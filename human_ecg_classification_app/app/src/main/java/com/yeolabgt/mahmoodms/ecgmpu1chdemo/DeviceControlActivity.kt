package com.yeolabgt.mahmoodms.ecgmpu1chdemo

import android.app.Activity
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothGattDescriptor
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothProfile
import android.content.Context
import android.content.Intent
import android.content.pm.ActivityInfo
import android.graphics.Color
import android.graphics.Typeface
import android.graphics.drawable.ColorDrawable
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.os.Handler
import android.support.v4.app.NavUtils
import android.support.v4.content.FileProvider
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.WindowManager
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import android.widget.ToggleButton

import com.androidplot.util.Redrawer
import com.yeolabgt.mahmoodms.actblelibrary.ActBle
import kotlinx.android.synthetic.main.activity_device_control.*
import org.tensorflow.contrib.android.TensorFlowInferenceInterface
import java.io.File

import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*

/**
 * Created by mahmoodms on 5/31/2016.
 * Android Activity for Controlling Bluetooth LE Device Connectivity
 */

class DeviceControlActivity : Activity(), ActBle.ActBleListener {
    // Graphing Variables:
    private var mGraphInitializedBoolean = false
    private var mGraphAdapterCh1: GraphAdapter? = null
    private var mGraphAdapterCh2: GraphAdapter? = null
    private var mGraphAdapterMotionAX: GraphAdapter? = null
    private var mGraphAdapterMotionAY: GraphAdapter? = null
    private var mGraphAdapterMotionAZ: GraphAdapter? = null
    private var mTimeDomainPlotAdapterCh1: XYPlotAdapter? = null
    //    private var mTimeDomainPlotAdapterCh2: XYPlotAdapter? = null
    private var mMotionDataPlotAdapter: XYPlotAdapter? = null
    //Device Information
    private var mBleInitializedBoolean = false
    private lateinit var mBluetoothGattArray: Array<BluetoothGatt?>
    private var mActBle: ActBle? = null
    private var mDeviceName: String? = null
    private var mDeviceAddress: String? = null
    private var mConnected: Boolean = false
    private var mMSBFirst = false
    //Connecting to Multiple Devices
    private var deviceMacAddresses: Array<String>? = null
    //UI Elements - TextViews, Buttons, etc
    private var mBatteryLevel: TextView? = null
    private var mDataRate: TextView? = null
    private var mChannelSelect: ToggleButton? = null
    private var menu: Menu? = null
    //Data throughput counter
    private var mLastTime: Long = 0
    private var mLastTime2: Long = 0
    private var points = 0
    private var points2 = 0
    private val mTimerHandler = Handler()
    private var mTimerEnabled = false
    //Data Variables:
    private val batteryWarning = 20
    private var dataRate: Double = 0.toDouble()
    // Tensorflow Implementation:
    private var mTFRunModel = false
    private var mTensorFlowInferenceInterface: TensorFlowInferenceInterface? = null
    private var mOutputScoresNames: Array<String>? = null
    private var mTensorflowInputXDim = 1L
    private var mTensorflowInputYDim = 1L
    private var mTensorflowOutputXDim = 1L
    private var mTensorflowOutputYDim = 1L
    private var mNumberOfClassifierCalls = 0


    private val mTimeStamp: String
        get() = SimpleDateFormat("yyyy.MM.dd_HH.mm.ss", Locale.US).format(Date())

    private val mClassifyThread = Runnable {
        if (mTFRunModel) {
            val outputProbabilities = FloatArray(2000 * outputClasses)
            val ecgRawDoubles = mCh1!!.classificationBuffer
            // Filter, level and return as floats:
            val inputArray = jecgFiltRescale(ecgRawDoubles)  //Float Array
            Log.e(TAG, "OrigArray: " + Arrays.toString(inputArray))
            mTensorFlowInferenceInterface!!.feed(INPUT_DATA_FEED_KEY, inputArray, 1L, mTensorflowInputXDim, mTensorflowInputYDim)
            mTensorFlowInferenceInterface!!.run(mOutputScoresNames)
            mTensorFlowInferenceInterface!!.fetch(OUTPUT_DATA_FEED_KEY, outputProbabilities)
            // Save outputProbabilities
            Log.e(TAG, "OutputArray: ${outputProbabilities.size}")
            val outputProbReshaped = jrearrange5c(outputProbabilities)
            // Distribute across 5 FAs:
            val outputProbClass0 = FloatArray(2000)
            val outputProbClass1 = FloatArray(2000)
            val outputProbClass2 = FloatArray(2000)
            val outputProbClass3 = FloatArray(2000)
            val outputProbClass4 = FloatArray(2000)
            System.arraycopy(outputProbReshaped, 0, outputProbClass0, 0, 2000)
            System.arraycopy(outputProbReshaped, 2000, outputProbClass1, 0, 2000)
            System.arraycopy(outputProbReshaped, 4000, outputProbClass2, 0, 2000)
            System.arraycopy(outputProbReshaped, 6000, outputProbClass3, 0, 2000)
            System.arraycopy(outputProbReshaped, 8000, outputProbClass4, 0, 2000)
            val yArray = jgetClassDist(outputProbReshaped)
            /*"C0: ${outputProbClass0.sum()} \n" +
                    "C1: ${outputProbClass1.sum()} \n" +
                    "C2: ${outputProbClass2.sum()} \n" +
                    "C3: ${outputProbClass3.sum()} \n" +
                    "C4: ${outputProbClass4.sum()} \n" +*/
            val s = "Output Class: ${yArray[0]} \n" +
                    "Array: ${Arrays.toString(yArray.slice(1..5).toFloatArray())}"
            runOnUiThread { classOutputText.text = s }
            // Save data:
            mTensorflowOutputsSaveFile?.writeToDiskFloat(inputArray, outputProbClass0, outputProbClass1, outputProbClass2, outputProbClass3, outputProbClass4)
        }
    }

    private fun enableTensorflowModel() {
        val classificationModelBinary = "opt_iptb_step_scnnd_u32_lr0.001.pb"
        val classificationModelPath = Environment.getExternalStorageDirectory().absolutePath +
                "/Download/tensorflow_assets/ecg_classify/" + classificationModelBinary
        Log.e(TAG, "Tensorflow classification Model Path: $classificationModelPath")
        mTensorflowInputXDim = 2000
        mTensorflowInputYDim = 1
        mTensorflowOutputXDim = 2000
        mTensorflowOutputYDim = 1
        when {
            File(classificationModelPath).exists() -> {
                mTensorFlowInferenceInterface = TensorFlowInferenceInterface(assets, classificationModelPath)
                // Reset counter:
                mNumberOfClassifierCalls = 1
                mTFRunModel = true
                Log.i(TAG, "Tensorflow - Custom classification Model Loaded: $classificationModelBinary")
            }
            else -> {
                mTFRunModel = false
                Toast.makeText(applicationContext, "No TF Model Found!", Toast.LENGTH_LONG).show()
            }
        }
        if (mTFRunModel) {
            Toast.makeText(applicationContext, "Tensorflow classification Model Loaded!", Toast.LENGTH_SHORT).show()
        }
    }

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_device_control)
        //Set orientation of device based on screen type/size:
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        //Receive Intents:
        val intent = intent
        deviceMacAddresses = intent.getStringArrayExtra(MainActivity.INTENT_DEVICES_KEY)
        val deviceDisplayNames = intent.getStringArrayExtra(MainActivity.INTENT_DEVICES_NAMES)
        mDeviceName = deviceDisplayNames[0]
        mDeviceAddress = deviceMacAddresses!![0]
        Log.d(TAG, "Device Names: " + Arrays.toString(deviceDisplayNames))
        Log.d(TAG, "Device MAC Addresses: " + Arrays.toString(deviceMacAddresses))
        Log.d(TAG, Arrays.toString(deviceMacAddresses))
        //Set up action bar:
        if (actionBar != null) {
            actionBar!!.setDisplayHomeAsUpEnabled(true)
        }
        val actionBar = actionBar
        actionBar!!.setBackgroundDrawable(ColorDrawable(Color.parseColor("#6078ef")))
        //Flag to keep screen on (stay-awake):
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        //Set up TextViews
        val mExportButton = findViewById<Button>(R.id.button_export)
        mBatteryLevel = findViewById(R.id.batteryText)
        mDataRate = findViewById(R.id.dataRate)
        mDataRate!!.text = "..."
        val ab = getActionBar()
        ab!!.title = mDeviceName
        ab.subtitle = mDeviceAddress
        //Initialize Bluetooth
        if (!mBleInitializedBoolean) initializeBluetoothArray()
        mLastTime = System.currentTimeMillis()
        //UI Listeners
        mChannelSelect = findViewById(R.id.toggleButtonGraph)
        mChannelSelect!!.setOnCheckedChangeListener { _, b ->
            mGraphAdapterCh1!!.clearPlot()
            mGraphAdapterCh2!!.clearPlot()
            mGraphAdapterCh1!!.plotData = b
            mGraphAdapterCh2!!.plotData = b
        }
        mExportButton.setOnClickListener { exportData() }
        // Tensorflow Switch
        tensorflowClassificationSwitch.setOnCheckedChangeListener { _, b ->
            if (b) {
                enableTensorflowModel()
            } else {
                mTFRunModel = false
                mNumberOfClassifierCalls = 1
                Toast.makeText(applicationContext, "Tensorflow Disabled", Toast.LENGTH_SHORT).show()
            }
        }
        mOutputScoresNames = arrayOf(OUTPUT_DATA_FEED_KEY)
    }

    private fun exportData() {
        try {
            terminateDataFileWriter()
        } catch (e: IOException) {
            Log.e(TAG, "IOException in saveDataFile")
            e.printStackTrace()
        }
        val files = ArrayList<Uri>()
        val context = applicationContext
        val uii = FileProvider.getUriForFile(context, context.packageName + ".provider", mPrimarySaveDataFile!!.file)
        files.add(uii)
        if (mSaveFileMPU != null) {
            val uii2 = FileProvider.getUriForFile(context, context.packageName + ".provider", mSaveFileMPU!!.file)
            files.add(uii2)
        }
        val uii3 = FileProvider.getUriForFile(context, context.packageName + ".provider", mTensorflowOutputsSaveFile!!.file)
        files.add(uii3)
        val exportData = Intent(Intent.ACTION_SEND_MULTIPLE)
        exportData.putExtra(Intent.EXTRA_SUBJECT, "ECG Sensor Data Export Details")
        exportData.putParcelableArrayListExtra(Intent.EXTRA_STREAM, files)
        exportData.type = "text/html"
        startActivity(exportData)
    }

    @Throws(IOException::class)
    private fun terminateDataFileWriter() {
        mPrimarySaveDataFile?.terminateDataFileWriter()
        mSaveFileMPU?.terminateDataFileWriter()
        mTensorflowOutputsSaveFile?.terminateDataFileWriter()
    }

    public override fun onResume() {
        jmainInitialization(true)
        if (mRedrawer != null) {
            mRedrawer!!.start()
        }
        super.onResume()
    }

    override fun onPause() {
        if (mRedrawer != null) mRedrawer!!.pause()
        super.onPause()
    }

    private fun initializeBluetoothArray() {
        val mBluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        val mBluetoothDeviceArray = arrayOfNulls<BluetoothDevice>(deviceMacAddresses!!.size)
        Log.d(TAG, "Device Addresses: " + Arrays.toString(deviceMacAddresses))
        if (deviceMacAddresses != null) {
            for (i in deviceMacAddresses!!.indices) {
                mBluetoothDeviceArray[i] = mBluetoothManager.adapter.getRemoteDevice(deviceMacAddresses!![i])
            }
        } else {
            Log.e(TAG, "No Devices Queued, Restart!")
            Toast.makeText(this, "No Devices Queued, Restart!", Toast.LENGTH_SHORT).show()
        }
        mActBle = ActBle(this, mBluetoothManager, this)
        mBluetoothGattArray = Array(deviceMacAddresses!!.size) { i -> mActBle!!.connect(mBluetoothDeviceArray[i]) }
        for (i in mBluetoothDeviceArray.indices) {
            Log.e(TAG, "Connecting to Device: " + (mBluetoothDeviceArray[i]!!.name + " " + mBluetoothDeviceArray[i]!!.address))
            if ("EMG 250Hz" == mBluetoothDeviceArray[i]!!.name) {
                mMSBFirst = false
            } else if (mBluetoothDeviceArray[i]!!.name != null) {
                if (mBluetoothDeviceArray[i]!!.name.toLowerCase().contains("nrf52")) {
                    mMSBFirst = true
                }
            }
            val str = mBluetoothDeviceArray[i]!!.name.toLowerCase()
            when {
                str.contains("8k") -> {
                    mSampleRate = 8000
                }
                str.contains("4k") -> {
                    mSampleRate = 4000
                }
                str.contains("2k") -> {
                    mSampleRate = 2000
                }
                str.contains("1k") -> {
                    mSampleRate = 1000
                }
                str.contains("500") -> {
                    mSampleRate = 500
                }
                else -> {
                    mSampleRate = 250
                }
            }
            mPacketBuffer = mSampleRate / 250
            Log.e(TAG, "mSampleRate: " + mSampleRate + "Hz")
            if (!mGraphInitializedBoolean) setupGraph()
//            mPrimarySaveDataFile = null
            createNewFile()
        }
        mBleInitializedBoolean = true
    }

    private fun createNewFile() {
        val directory = "/ECGData"
        val fileNameTimeStamped = "ECGData_" + mTimeStamp + "_" + mSampleRate.toString() + "Hz"
        if (mPrimarySaveDataFile == null) {
            Log.e(TAG, "fileTimeStamp: $fileNameTimeStamped")
            mPrimarySaveDataFile = SaveDataFile(directory, fileNameTimeStamped,
                    24, 1.toDouble() / mSampleRate, true, false)
        } else if (!mPrimarySaveDataFile!!.initialized) {
            Log.e(TAG, "New Filename: $fileNameTimeStamped")
            mPrimarySaveDataFile?.createNewFile(directory, fileNameTimeStamped)
        }

        // Tensorflow Stuff:
        val directory2 = "/ECG_TF_data_out"
        val fileNameTimeStamped2 = "ECG_TF_data_" + mTimeStamp + "_" + mSampleRate.toString() + "Hz"
        if (mTensorflowOutputsSaveFile == null) {
            Log.e(TAG, "fileTimeStamp: $fileNameTimeStamped2")
            mTensorflowOutputsSaveFile = SaveDataFile(directory2, fileNameTimeStamped2, 24, 1.toDouble() / mSampleRate,
                    saveTimestamps = false, includeClass = false)
        }
    }

    private fun createNewFileMPU() {
        val directory = "/MPUData"
        val fileNameTimeStamped = "MPUData_$mTimeStamp"
        if (mSaveFileMPU == null) {
            Log.e(TAG, "fileTimeStamp: $fileNameTimeStamped")
            mSaveFileMPU = SaveDataFile(directory, fileNameTimeStamped,
                    16, 0.032, true, false)
        } else if (!mSaveFileMPU!!.initialized) {
            Log.e(TAG, "New Filename: $fileNameTimeStamped")
            mSaveFileMPU?.createNewFile(directory, fileNameTimeStamped)
        }
    }

    private fun setupGraph() {
        // Initialize our XYPlot reference:
        mGraphAdapterCh1 = GraphAdapter(1250, "ECG Data Ch 1", false, Color.BLUE)
        mGraphAdapterCh2 = GraphAdapter(1250, "ECG Data Ch 2", false, Color.RED)
        mGraphAdapterMotionAX = GraphAdapter(375, "Acc X", false, Color.RED)
        mGraphAdapterMotionAY = GraphAdapter(375, "Acc Y", false, Color.GREEN)
        mGraphAdapterMotionAZ = GraphAdapter(375, "Acc Z", false, Color.BLUE)
        //PLOT CH1 By default
        mGraphAdapterCh1!!.setPointWidth(2.toFloat())
        mGraphAdapterCh2!!.setPointWidth(2.toFloat())
        mGraphAdapterMotionAX?.setPointWidth(2.toFloat())
        mGraphAdapterMotionAY?.setPointWidth(2.toFloat())
        mGraphAdapterMotionAZ?.setPointWidth(2.toFloat())
        mTimeDomainPlotAdapterCh1 = XYPlotAdapter(findViewById(R.id.ecgTimeDomainXYPlot), false, if (mSampleRate < 1000) 4 * mSampleRate else 2000)
        mTimeDomainPlotAdapterCh1?.xyPlot?.addSeries(mGraphAdapterCh1!!.series, mGraphAdapterCh1!!.lineAndPointFormatter)
        mMotionDataPlotAdapter = XYPlotAdapter(findViewById(R.id.motionDataPlot), "Time (s)", "Acc (g)", 375.0)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAX?.series, mGraphAdapterMotionAX?.lineAndPointFormatter)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAY?.series, mGraphAdapterMotionAY?.lineAndPointFormatter)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAZ?.series, mGraphAdapterMotionAZ?.lineAndPointFormatter)
        val xyPlotList = listOf(mTimeDomainPlotAdapterCh1?.xyPlot, mMotionDataPlotAdapter?.xyPlot)
        mRedrawer = Redrawer(xyPlotList, 30f, false)
        mRedrawer!!.start()
        mGraphInitializedBoolean = true

        mGraphAdapterMotionAX?.setxAxisIncrement(0.032)
        mGraphAdapterMotionAX?.setSeriesHistoryDataPoints(375)
        mGraphAdapterMotionAY?.setxAxisIncrement(0.032)
        mGraphAdapterMotionAY?.setSeriesHistoryDataPoints(375)
        mGraphAdapterMotionAZ?.setxAxisIncrement(0.032)
        mGraphAdapterMotionAZ?.setSeriesHistoryDataPoints(375)

        mGraphAdapterCh1!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterCh2!!.setxAxisIncrementFromSampleRate(mSampleRate)

        mGraphAdapterCh1!!.setSeriesHistoryDataPoints(1250)
        mGraphAdapterCh2!!.setSeriesHistoryDataPoints(1250)
    }

    private fun setNameAddress(name_action: String?, address_action: String?) {
        val name = menu!!.findItem(R.id.action_title)
        val address = menu!!.findItem(R.id.action_address)
        name.title = name_action
        address.title = address_action
        invalidateOptionsMenu()
    }

    override fun onDestroy() {
        mRedrawer?.finish()
        disconnectAllBLE()
        try {
            terminateDataFileWriter()
        } catch (e: IOException) {
            Log.e(TAG, "IOException in saveDataFile")
            e.printStackTrace()
        }

        stopMonitoringRssiValue()
        jmainInitialization(false) //Just a technicality, doesn't actually do anything
        super.onDestroy()
    }

    private fun disconnectAllBLE() {
        if (mActBle != null) {
            for (bluetoothGatt in mBluetoothGattArray) {
                mActBle!!.disconnect(bluetoothGatt!!)
                mConnected = false
                resetMenuBar()
            }
        }
    }

    private fun resetMenuBar() {
        runOnUiThread {
            if (menu != null) {
                menu!!.findItem(R.id.menu_connect).isVisible = true
                menu!!.findItem(R.id.menu_disconnect).isVisible = false
            }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.menu_device_control, menu)
        menuInflater.inflate(R.menu.actionbar_item, menu)
        if (mConnected) {
            menu.findItem(R.id.menu_connect).isVisible = false
            menu.findItem(R.id.menu_disconnect).isVisible = true
        } else {
            menu.findItem(R.id.menu_connect).isVisible = true
            menu.findItem(R.id.menu_disconnect).isVisible = false
        }
        this.menu = menu
        setNameAddress(mDeviceName, mDeviceAddress)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.menu_connect -> {
                if (mActBle != null) {
                    initializeBluetoothArray()
                }
                connect()
                return true
            }
            R.id.menu_disconnect -> {
                if (mActBle != null) {
                    disconnectAllBLE()
                }
                return true
            }
            android.R.id.home -> {
                if (mActBle != null) {
                    disconnectAllBLE()
                }
                NavUtils.navigateUpFromSameTask(this)
                onBackPressed()
                return true
            }
            R.id.action_settings -> {
                launchSettingsMenu()
                return true
            }
            R.id.action_export -> {
                exportData()
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (requestCode == 1) {
            val context = applicationContext
            //UI Stuff:
            val chSel = PreferencesFragment.channelSelect(context)
            //File Save Stuff
            val saveTimestamps = PreferencesFragment.saveTimestamps(context)
            val precision = (if (PreferencesFragment.setBitPrecision(context)) 64 else 32).toShort()
            val saveClass = PreferencesFragment.saveClass(context)
            mPrimarySaveDataFile!!.setSaveTimestamps(saveTimestamps)
            mPrimarySaveDataFile!!.setFpPrecision(precision)
            mPrimarySaveDataFile!!.setIncludeClass(saveClass)
            val filterData = PreferencesFragment.setFilterData(context)
            if (mGraphAdapterCh1 != null) {
                mFilterData = filterData
            }

            mTimeDomainPlotAdapterCh1!!.xyPlot?.redraw()
            mChannelSelect!!.isChecked = chSel
            mGraphAdapterCh1!!.plotData = chSel
            mGraphAdapterCh2!!.plotData = chSel
        }
        super.onActivityResult(requestCode, resultCode, data)
    }

    private fun launchSettingsMenu() {
        val intent = Intent(applicationContext, SettingsActivity::class.java)
        startActivityForResult(intent, 1)
    }

    private fun connect() {
        runOnUiThread {
            val menuItem = menu!!.findItem(R.id.action_status)
            menuItem.title = "Connecting..."
        }
    }

    override fun onServicesDiscovered(gatt: BluetoothGatt, status: Int) {
        Log.i(TAG, "onServicesDiscovered")
        if (status == BluetoothGatt.GATT_SUCCESS) {
            for (service in gatt.services) {
                if (service == null || service.uuid == null) {
                    continue
                }
                if (AppConstant.SERVICE_DEVICE_INFO == service.uuid) {
                    //Read the device serial number (if available)
                    if (service.getCharacteristic(AppConstant.CHAR_SERIAL_NUMBER) != null) {
                        mActBle!!.readCharacteristic(gatt, service.getCharacteristic(AppConstant.CHAR_SERIAL_NUMBER))
                    }
                    //Read the device software version (if available)
                    if (service.getCharacteristic(AppConstant.CHAR_SOFTWARE_REV) != null) {
                        mActBle!!.readCharacteristic(gatt, service.getCharacteristic(AppConstant.CHAR_SOFTWARE_REV))
                    }
                }
                if (AppConstant.SERVICE_EEG_SIGNAL == service.uuid) {
                    if (service.getCharacteristic(AppConstant.CHAR_EEG_CH1_SIGNAL) != null) {
                        mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_EEG_CH1_SIGNAL), true)
                    }
                    if (service.getCharacteristic(AppConstant.CHAR_EEG_CH2_SIGNAL) != null) {
                        mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_EEG_CH2_SIGNAL), true)
                    }
                    if (service.getCharacteristic(AppConstant.CHAR_EEG_CH3_SIGNAL) != null) {
                        mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_EEG_CH3_SIGNAL), true)
                    }
                    if (service.getCharacteristic(AppConstant.CHAR_EEG_CH4_SIGNAL) != null) {
                        mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_EEG_CH4_SIGNAL), true)
                    }
                }

                if (AppConstant.SERVICE_BATTERY_LEVEL == service.uuid) { //Read the device battery percentage
                    mActBle!!.readCharacteristic(gatt, service.getCharacteristic(AppConstant.CHAR_BATTERY_LEVEL))
                    mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_BATTERY_LEVEL), true)
                }

                if (AppConstant.SERVICE_MPU == service.uuid) {
                    mActBle!!.setCharacteristicNotifications(gatt, service.getCharacteristic(AppConstant.CHAR_MPU_COMBINED), true)
                    //TODO: INITIALIZE MPU FILE HERE:
                    mMPU = DataChannel(false, true, 0)
//                    mSaveFileMPU = null
                    createNewFileMPU()
                }
            }
            //Run process only once:
            mActBle?.runProcess()
        }
    }

    override fun onCharacteristicRead(gatt: BluetoothGatt, characteristic: BluetoothGattCharacteristic, status: Int) {
        Log.i(TAG, "onCharacteristicRead")
        if (status == BluetoothGatt.GATT_SUCCESS) {
            if (AppConstant.CHAR_BATTERY_LEVEL == characteristic.uuid) {
                if (characteristic.value != null) {
                    val batteryLevel = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0)
                    updateBatteryStatus(batteryLevel)
                    Log.i(TAG, "Battery Level :: $batteryLevel")
                }
            }
        } else {
            Log.e(TAG, "onCharacteristic Read Error$status")
        }
    }

    override fun onCharacteristicChanged(gatt: BluetoothGatt, characteristic: BluetoothGattCharacteristic) {
        if (mCh1 == null || mCh2 == null) {
            mCh1 = DataChannel(false, mMSBFirst, 8 * mSampleRate)
            mCh2 = DataChannel(false, mMSBFirst, 8 * mSampleRate)
        }

        if (AppConstant.CHAR_BATTERY_LEVEL == characteristic.uuid) {
            val batteryLevel = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0)!!
            updateBatteryStatus(batteryLevel)
        }

        if (AppConstant.CHAR_EEG_CH1_SIGNAL == characteristic.uuid) {
            if (!mCh1!!.chEnabled) mCh1!!.chEnabled = true
            val mNewEEGdataBytes = characteristic.value
            getDataRateBytes(mNewEEGdataBytes.size)
            mCh1!!.handleNewData(mNewEEGdataBytes)
            addToGraphBuffer(mCh1!!, mGraphAdapterCh1)
            mPrimarySaveDataFile!!.writeToDisk(mCh1!!.characteristicDataPacketBytes)
            // For every 2000 dp recieved, run classification model.
            //TODO: FIX THIS, it triggers in the following arrangement: [3120, 6240, 9360 ... ] (12+ seconds).
            Log.e(TAG, "mCh1.dataPointCounterClassify: ${mCh1!!.dataPointCounterClassify}")
            if (mCh1!!.dataPointCounterClassify > 1000) {
                Log.e(TAG, "Total datapoints: ${mCh1!!.totalDataPointsReceived}")
                mCh1?.resetCounterClassify()
                val classifyTaskThread = Thread(mClassifyThread)
                classifyTaskThread.start()
            }
        }

        if (AppConstant.CHAR_EEG_CH2_SIGNAL == characteristic.uuid) {
            if (mCh2!!.chEnabled) mCh2!!.chEnabled = true
        }

        if (AppConstant.CHAR_MPU_COMBINED == characteristic.uuid) {
            val dataMPU = characteristic.value
            getDataRateBytes2(dataMPU.size) //+=240
            mMPU!!.handleNewData(dataMPU)
            addToGraphBufferMPU(mMPU!!)
            mSaveFileMPU!!.exportDataWithTimestampMPU(mMPU!!.characteristicDataPacketBytes)
            if (mSaveFileMPU!!.mLinesWrittenCurrentFile > 1048576) {
                mSaveFileMPU!!.terminateDataFileWriter()
                createNewFileMPU()
            }
        }
    }

    private fun addToGraphBuffer(dataChannel: DataChannel, graphAdapter: GraphAdapter?) {
        if (mFilterData && dataChannel.totalDataPointsReceived > 4 * mSampleRate/* && mSampleRate < 1000*/) {
            val graphBufferLength = 4 * 250
            //TODO: Downsample, then filter, then plot:
            val filterArray = jdownSample(dataChannel.classificationBuffer, mSampleRate)
            graphAdapter?.setSeriesHistoryDataPoints(graphBufferLength)
            val filteredData = jecgBandStopFilter(filterArray)
            graphAdapter!!.clearPlot()

            for (i in filteredData.indices) { // gA.addDataPointTimeDomain(y,x)
                graphAdapter.addDataPointTimeDomainAlt(filteredData[i], dataChannel.totalDataPointsReceived - (graphBufferLength - 1) + i)
            }
        } else {
            if (dataChannel.dataBuffer != null) {
                graphAdapter?.setSeriesHistoryDataPoints(1250)
                if (mPrimarySaveDataFile!!.resolutionBits == 24) {
                    var i = 0
                    while (i < dataChannel.dataBuffer!!.size / 3) {
                        graphAdapter!!.addDataPointTimeDomain(DataChannel.bytesToDouble(dataChannel.dataBuffer!![3 * i],
                                dataChannel.dataBuffer!![3 * i + 1], dataChannel.dataBuffer!![3 * i + 2]),
                                dataChannel.totalDataPointsReceived - dataChannel.dataBuffer!!.size / 3 + i)
                        i += graphAdapter.sampleRate / 250
                    }
                } else if (mPrimarySaveDataFile!!.resolutionBits == 16) {
                    var i = 0
                    while (i < dataChannel.dataBuffer!!.size / 2) {
                        graphAdapter!!.addDataPointTimeDomain(DataChannel.bytesToDouble(dataChannel.dataBuffer!![2 * i],
                                dataChannel.dataBuffer!![2 * i + 1]),
                                dataChannel.totalDataPointsReceived - dataChannel.dataBuffer!!.size / 2 + i)
                        i += graphAdapter.sampleRate / 250
                    }
                }
            }
        }
        dataChannel.resetBuffer()
    }

    private fun addToGraphBufferMPU(dataChannel: DataChannel) {
        if (dataChannel.dataBuffer != null) {
            for (i in 0 until dataChannel.dataBuffer!!.size / 12) {
                mGraphAdapterMotionAX?.addDataPointTimeDomain(DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i], dataChannel.dataBuffer!![12 * i + 1]), mTimestampIdxMPU)
                mGraphAdapterMotionAY?.addDataPointTimeDomain(DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i + 2], dataChannel.dataBuffer!![12 * i + 3]), mTimestampIdxMPU)
                mGraphAdapterMotionAZ?.addDataPointTimeDomain(DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i + 4], dataChannel.dataBuffer!![12 * i + 5]), mTimestampIdxMPU)
                mTimestampIdxMPU += 1
            }
        }
        dataChannel.resetBuffer()
    }

    private fun getDataRateBytes(bytes: Int) {
        val mCurrentTime = System.currentTimeMillis()
        points += bytes
        if (mCurrentTime > mLastTime + 5000) {
            dataRate = (points / 5).toDouble()
            points = 0
            mLastTime = mCurrentTime
            Log.e(" DataRate:", dataRate.toString() + " Bytes/s")
            runOnUiThread {
                val s = dataRate.toString() + " Bytes/s"
                mDataRate!!.text = s
            }
        }
    }

    private fun getDataRateBytes2(bytes: Int) {
        val mCurrentTime = System.currentTimeMillis()
        points2 += bytes
        if (mCurrentTime > mLastTime2 + 3000) {
            val datarate2 = (points2 / 3).toDouble()
            points2 = 0
            mLastTime2 = mCurrentTime
            Log.e(" DataRate 2(MPU):", datarate2.toString() + " Bytes/s")
        }
    }

    override fun onReadRemoteRssi(gatt: BluetoothGatt, rssi: Int, status: Int) {
        uiRssiUpdate(rssi)
    }

    override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
        when (newState) {
            BluetoothProfile.STATE_CONNECTED -> {
                mConnected = true
                runOnUiThread {
                    if (menu != null) {
                        menu!!.findItem(R.id.menu_connect).isVisible = false
                        menu!!.findItem(R.id.menu_disconnect).isVisible = true
                    }
                }
                Log.i(TAG, "Connected")
                updateConnectionState(getString(R.string.connected))
                invalidateOptionsMenu()
                runOnUiThread {
                    mDataRate!!.setTextColor(Color.BLACK)
                    mDataRate!!.setTypeface(null, Typeface.NORMAL)
                }
                //Start the service discovery:
                gatt.discoverServices()
                startMonitoringRssiValue()
            }
            BluetoothProfile.STATE_CONNECTING -> {
            }
            BluetoothProfile.STATE_DISCONNECTING -> {
            }
            BluetoothProfile.STATE_DISCONNECTED -> {
                mConnected = false
                runOnUiThread {
                    if (menu != null) {
                        menu!!.findItem(R.id.menu_connect).isVisible = true
                        menu!!.findItem(R.id.menu_disconnect).isVisible = false
                    }
                }
                Log.i(TAG, "Disconnected")
                runOnUiThread {
                    mDataRate!!.setTextColor(Color.RED)
                    mDataRate!!.setTypeface(null, Typeface.BOLD)
                    mDataRate!!.text = HZ
                }
                updateConnectionState(getString(R.string.disconnected))
                stopMonitoringRssiValue()
                invalidateOptionsMenu()
            }
            else -> {
            }
        }
    }

    private fun startMonitoringRssiValue() {
        readPeriodicallyRssiValue(true)
    }

    private fun stopMonitoringRssiValue() {
        readPeriodicallyRssiValue(false)
    }

    private fun readPeriodicallyRssiValue(repeat: Boolean) {
        mTimerEnabled = repeat
        // check if we should stop checking RSSI value
        if (!mConnected || !mTimerEnabled) {
            mTimerEnabled = false
            return
        }

        mTimerHandler.postDelayed(Runnable {
            if (!mConnected) {
                mTimerEnabled = false
                return@Runnable
            }
            // request RSSI value
            mBluetoothGattArray[0]!!.readRemoteRssi()
            // add call it once more in the future
            readPeriodicallyRssiValue(mTimerEnabled)
        }, RSSI_UPDATE_TIME_INTERVAL.toLong())
    }

    override fun onCharacteristicWrite(gatt: BluetoothGatt, characteristic: BluetoothGattCharacteristic, status: Int) {
        Log.i(TAG, "onCharacteristicWrite :: Status:: $status")
    }

    override fun onDescriptorWrite(gatt: BluetoothGatt, descriptor: BluetoothGattDescriptor, status: Int) {}

    override fun onDescriptorRead(gatt: BluetoothGatt, descriptor: BluetoothGattDescriptor, status: Int) {
        Log.i(TAG, "onDescriptorRead :: Status:: $status")
    }

    override fun onError(errorMessage: String) {
        Log.e(TAG, "Error:: $errorMessage")
    }

    private fun updateConnectionState(status: String) {
        runOnUiThread {
            if (status == getString(R.string.connected)) {
                Toast.makeText(applicationContext, "Device Connected!", Toast.LENGTH_SHORT).show()
            } else if (status == getString(R.string.disconnected)) {
                Toast.makeText(applicationContext, "Device Disconnected!", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun updateBatteryStatus(integerValue: Int) {
        val status: String
        val convertedBatteryVoltage = integerValue.toDouble() / 4096.0 * 7.20
        //Because TPS63001 dies below 1.8V, we need to set up a linear fit between 1.8-4.2V
        //Anything over 4.2V = 100%
        val finalPercent: Double = when {
            125.0 / 3.0 * convertedBatteryVoltage - 75.0 > 100.0 -> 100.0
            125.0 / 3.0 * convertedBatteryVoltage - 75.0 < 0.0 -> 0.0
            else -> 125.0 / 3.0 * convertedBatteryVoltage - 75.0
        }
        Log.e(TAG, "Battery Integer Value: " + integerValue.toString())
        Log.e(TAG, "ConvertedBatteryVoltage: " + String.format(Locale.US, "%.5f", convertedBatteryVoltage) + "V : " + String.format(Locale.US, "%.3f", finalPercent) + "%")
        status = String.format(Locale.US, "%.1f", finalPercent) + "%"
        runOnUiThread {
            if (finalPercent <= batteryWarning) {
                mBatteryLevel!!.setTextColor(Color.RED)
                mBatteryLevel!!.setTypeface(null, Typeface.BOLD)
                Toast.makeText(applicationContext, "Charge Battery, Battery Low $status", Toast.LENGTH_SHORT).show()
            } else {
                mBatteryLevel!!.setTextColor(Color.GREEN)
                mBatteryLevel!!.setTypeface(null, Typeface.BOLD)
            }
            mBatteryLevel!!.text = status
        }
    }

    private fun uiRssiUpdate(rssi: Int) {
        runOnUiThread {
            val menuItem = menu!!.findItem(R.id.action_rssi)
            val statusActionItem = menu!!.findItem(R.id.action_status)
            val valueOfRSSI = rssi.toString() + " dB"
            menuItem.title = valueOfRSSI
            if (mConnected) {
                val newStatus = "Status: " + getString(R.string.connected)
                statusActionItem.title = newStatus
            } else {
                val newStatus = "Status: " + getString(R.string.disconnected)
                statusActionItem.title = newStatus
            }
        }
    }

    private external fun jdownSample(data: DoubleArray, sampleRate: Int): DoubleArray

    private external fun jecgBandStopFilter(data: DoubleArray): DoubleArray

    private external fun jmainInitialization(initialize: Boolean): Int

    private external fun jecgFiltRescale(data: DoubleArray): FloatArray

    private external fun jrearrange5c(data: FloatArray): FloatArray

    private external fun jrearrange2c(data: FloatArray): FloatArray

    private external fun jgetClassDist(data: FloatArray): FloatArray

    companion object {
        const val HZ = "0 Hz"
        private const val INPUT_DATA_FEED_KEY = "input_1"
        private const val OUTPUT_DATA_FEED_KEY = "dense_1/truediv"
        private val TAG = DeviceControlActivity::class.java.simpleName
        var mRedrawer: Redrawer? = null
        // Power Spectrum Graph Data:
        private var mSampleRate = 250
        //Data Channel Classes
        internal var mCh1: DataChannel? = null
        internal var mCh2: DataChannel? = null
        internal var mMPU: DataChannel? = null
        internal var mFilterData = false
        private var mPacketBuffer = 6
        private var mTimestampIdxMPU = 0
        //RSSI:
        private const val RSSI_UPDATE_TIME_INTERVAL = 2000
        private const val outputClasses = 5
        var mSSVEPClass = 0.0
        //Save Data File
        private var mPrimarySaveDataFile: SaveDataFile? = null
        private var mTensorflowOutputsSaveFile: SaveDataFile? = null
        private var mSaveFileMPU: SaveDataFile? = null

        init {
            System.loadLibrary("ecg-lib")
        }
    }
}
