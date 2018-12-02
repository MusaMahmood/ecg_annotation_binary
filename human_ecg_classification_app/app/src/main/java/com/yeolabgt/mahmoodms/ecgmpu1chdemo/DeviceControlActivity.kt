package com.yeolabgt.mahmoodms.ecgmpu1chdemo

import android.app.Activity
import android.bluetooth.*
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
import com.androidplot.util.Redrawer
import com.google.common.primitives.Doubles
import com.yeolabgt.mahmoodms.actblelibrary.ActBle
import kotlinx.android.synthetic.main.activity_device_control_classify.*
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
    private var mGraphAdapterClass0: GraphAdapter? = null
    private var mGraphAdapterClass1: GraphAdapter? = null
    private var mGraphAdapterClass2: GraphAdapter? = null
    private var mGraphAdapterClass3: GraphAdapter? = null
    private var mGraphAdapterClass4: GraphAdapter? = null
    private var mGraphAdapterMotionAX: GraphAdapter? = null
    private var mGraphAdapterMotionAY: GraphAdapter? = null
    private var mGraphAdapterMotionAZ: GraphAdapter? = null
    private var mTimeDomainPlotAdapterCh1: XYPlotAdapter? = null
    private var mClassificationLabelsPlotAdapter: XYPlotAdapter? = null
    private var mMotionDataPlotAdapter: XYPlotAdapter? = null
    private var mCurrentIndex = 0
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
    private var mTFRunModel = true
    private var mTensorFlowInferenceInterfaceEcg: TensorFlowInferenceInterface? = null
    private var mOutputScoresNamesEcg: Array<String>? = null
    private var mTensorflowInputXDim = 1L
    private var mTensorflowInputYDim = 1L
    private var mTensorflowOutputXDim = 1L
    private var mTensorflowOutputYDim = 1L
    // TF Implementation for Activity data:
    private var mTensorFlowInferenceInterfaceActivity: TensorFlowInferenceInterface? = null
    private var mOutputScoresNamesActivity: Array<String>? = null
    private var mTFRunModelActivity = true
    private val mAccXBuffer = DoubleArray(256)
    private val mAccYBuffer = DoubleArray(256)
    private val mAccZBuffer = DoubleArray(256)
    private val mGyrXBuffer = DoubleArray(256)
    private val mGyrYBuffer = DoubleArray(256)
    private val mGyrZBuffer = DoubleArray(256)
    // HR/RR:
    private var mHRRREnabled = false


    private val mTimeStamp: String
        get() = SimpleDateFormat("yyyy.MM.dd_HH.mm.ss", Locale.US).format(Date())

    private fun getArgMax(floatArray: FloatArray): Int {
        var largest = 0
        for (i in 1 until floatArray.size) {
            if (floatArray[i] > floatArray[largest])
                largest = i
        }
        return largest
    }

    private val mClassifyActivityThread = Runnable {
        if (mTFRunModelActivity) {
            val outputProbabilities = FloatArray(6)
            val doubleArrayAccGyr = Doubles.concat(mAccXBuffer, mAccYBuffer, mAccZBuffer, mGyrXBuffer, mGyrYBuffer, mGyrZBuffer)
            val inputFeatures = jactivPrep(doubleArrayAccGyr)
            Log.e(TAG, "inputFeatures: ${Arrays.toString(inputFeatures)}")
            mTensorFlowInferenceInterfaceActivity?.feed(INPUT_DATA_ACTIV_KEY, inputFeatures, 1L/*batch*/, 256L/*x_dim*/, 8L/*y_dim*/)
            mTensorFlowInferenceInterfaceActivity?.run(mOutputScoresNamesActivity)
            mTensorFlowInferenceInterfaceActivity?.fetch(OUTPUT_DATA_ACTIV_KEY, outputProbabilities)
            Log.e(TAG, "Activity: OutputProbs: ${Arrays.toString(outputProbabilities)}")
            //Save Data:
            val outputArray0 = DoubleArray(256) {outputProbabilities[0].toDouble()}
            val outputArray1 = DoubleArray(256) {outputProbabilities[1].toDouble()}
            val outputArray2 = DoubleArray(256) {outputProbabilities[2].toDouble()}
            val outputArray3 = DoubleArray(256) {outputProbabilities[3].toDouble()}
            val outputArray4 = DoubleArray(256) {outputProbabilities[4].toDouble()}
            val outputArray5 = DoubleArray(256) {outputProbabilities[5].toDouble()}
            mSaveFileMPUOutputs?.writeToDiskDouble(mAccXBuffer, mAccYBuffer, mAccZBuffer, mGyrXBuffer, mGyrYBuffer, mGyrZBuffer,
                    outputArray0, outputArray1, outputArray2,outputArray3, outputArray4, outputArray5)
            val outputClass = getArgMax(outputProbabilities)
            val s = when (outputClass) {
                0 -> "Idle"
                1 -> "Walking"
                2 -> "Running"
                3 -> "Stairs, Down"
                4 -> "Stairs, Up"
                5 -> "Fall Detected!"
                else -> ""
            }
            val outputString = "Current Activity: $s"
            runOnUiThread {textViewActivity.text = outputString}
        }
    }

    private val mClassifyThread = Runnable {
        if (mTFRunModel) {
            val currentTimeStamp = mCh1!!.totalDataPointsReceived.toDouble() / mSampleRate.toDouble()
            val outputProbabilities = FloatArray(2000 * outputClasses)
            val ecgRawDoubles = mCh1!!.classificationBuffer
            //Select last 2000 values for saving.
            val ecgRawDoublesCrop = DoubleArray(2000)
            System.arraycopy(ecgRawDoubles, 5499/*len-2000-1*/, ecgRawDoublesCrop, 0, 2000)
            // Filter, level and return as floats:
            val inputArray = jecgFiltRescale(ecgRawDoublesCrop)  //Float Array
            mTensorFlowInferenceInterfaceEcg?.feed(INPUT_DATA_FEED_KEY, inputArray, 1L, mTensorflowInputXDim, mTensorflowInputYDim)
            mTensorFlowInferenceInterfaceEcg?.run(mOutputScoresNamesEcg)
            mTensorFlowInferenceInterfaceEcg?.fetch(OUTPUT_DATA_FEED_KEY, outputProbabilities)
            // Save outputProbabilities
            Log.e(TAG, "OutputArray.size: ${outputProbabilities.size}")
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

            // Save data:
            mTensorflowOutputsSaveFile?.writeToDiskFloat(inputArray, outputProbClass0, outputProbClass1, outputProbClass2, outputProbClass3, outputProbClass4)
            val outputProbsSmoothed = jreturnSmoothedLabels(outputProbReshaped)
            System.arraycopy(outputProbsSmoothed, 0, outputProbClass0, 0, 2000)
            System.arraycopy(outputProbsSmoothed, 2000, outputProbClass1, 0, 2000)
            System.arraycopy(outputProbsSmoothed, 4000, outputProbClass2, 0, 2000)
            System.arraycopy(outputProbsSmoothed, 6000, outputProbClass3, 0, 2000)
            System.arraycopy(outputProbsSmoothed, 8000, outputProbClass4, 0, 2000)
            runOnUiThread {
                addToGraphBuffer(mGraphAdapterCh1!!, inputArray, mCurrentIndex)
                addToGraphBuffer(mGraphAdapterClass0!!, outputProbClass0, mCurrentIndex)
                addToGraphBuffer(mGraphAdapterClass1!!, outputProbClass1, mCurrentIndex)
                addToGraphBuffer(mGraphAdapterClass2!!, outputProbClass2, mCurrentIndex)
                addToGraphBuffer(mGraphAdapterClass3!!, outputProbClass3, mCurrentIndex)
                addToGraphBuffer(mGraphAdapterClass4!!, outputProbClass4, mCurrentIndex)
            }
            //Stuff for Logging.
            val yArray = jgetClassDist(outputProbReshaped)
            val yArray2 = jgetClassDist(outputProbsSmoothed)
            val s = "Output Class: ${yArray[0]} \n" +
                    "Array: ${Arrays.toString(yArray.slice(1..5).toFloatArray())}" +
                    "Smoothed Output Class: ${yArray2[0]} \n" +
                    "Smoothed Array: ${Arrays.toString(yArray2.slice(1..5).toFloatArray())}"
            Log.e(TAG, "ClassificationOutput: $s")
            if (mHRRREnabled) {
                val hrrr = jGetHRRR(ecgRawDoubles) /*inputArray.map { it.toDouble() }.toDoubleArray()*/
                val hrString = "Heart Rate: %1.2f bpm".format(hrrr[0]) + " Resp Rate: %1.2f breaths/min".format(hrrr[1])
                runOnUiThread { textViewHR.text = hrString }
                // Save Data as: [ Time Stamp (s), HR, RR ]
                mEcgHeartRespiratoryFile!!.exportFileDouble(currentTimeStamp, hrrr[0], hrrr[1])
            }
        }
    }

    private fun enableTensorflowModel() {
        val classificationModelBinary = "opt_iptb_inception.v2.8_0.001.pb"
        val classificationModelPath = Environment.getExternalStorageDirectory().absolutePath +
                "/Download/tensorflow_assets/ecg_classify/" + classificationModelBinary
        Log.e(TAG, "Tensorflow ECG classification Model Path: $classificationModelPath")
        mTensorflowInputXDim = 2000
        mTensorflowInputYDim = 1
        mTensorflowOutputXDim = 2000
        mTensorflowOutputYDim = 1
        when {
            File(classificationModelPath).exists() -> {
                mTensorFlowInferenceInterfaceEcg = TensorFlowInferenceInterface(assets, classificationModelPath)
                // Reset counter:
                mTFRunModel = true
                Log.i(TAG, "Tensorflow - Custom classification Model Loaded: $classificationModelBinary")
            }
            else -> {
                mTFRunModel = false
                Toast.makeText(applicationContext, "ECG TF Model Missing!", Toast.LENGTH_LONG).show()
            }
        }
        // Enable Activity Model:
        val classificationModelBinaryActivity = "opt_activity256_classify_v0.pb"
        val classificationModelPathActivity = Environment.getExternalStorageDirectory().absolutePath +
                "/Download/tensorflow_assets/activity_classify/" + classificationModelBinaryActivity
        Log.e(TAG, "Tensorflow Activity classification Model Path: $classificationModelPathActivity")
        when {
            File(classificationModelPathActivity).exists() -> {
                mTensorFlowInferenceInterfaceActivity = TensorFlowInferenceInterface(assets, classificationModelPathActivity)
                Log.i(TAG, "Tensorflow - Custom classification Model Loaded: $classificationModelBinaryActivity")
                mTFRunModelActivity = true
            }
            else -> {
                Toast.makeText(applicationContext, "Activity TF Model Missing!", Toast.LENGTH_LONG).show()
                mTFRunModelActivity = true
            }
        }

        if (mTFRunModel and mTFRunModelActivity) {
            Toast.makeText(applicationContext, "Tensorflow classification Models Loaded!", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(applicationContext, "One or more classification models missing!", Toast.LENGTH_LONG).show()
        }
    }

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_device_control_classify)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
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
        //UI Listeners
        mExportButton.setOnClickListener { exportData() }
        // Tensorflow Switch
        tensorflowClassificationToggle.setOnCheckedChangeListener { _, b ->
            if (b) {
                enableTensorflowModel()
            } else {
                mTFRunModel = false
                mTFRunModelActivity = false
                Toast.makeText(applicationContext, "Tensorflow Disabled", Toast.LENGTH_SHORT).show()
            }
        }
        mOutputScoresNamesEcg = arrayOf(OUTPUT_DATA_FEED_KEY)
        mOutputScoresNamesActivity = arrayOf(OUTPUT_DATA_ACTIV_KEY)
        if (mTFRunModel) {
            enableTensorflowModel()
        }

        //Initialize Bluetooth
        if (!mBleInitializedBoolean) initializeBluetoothArray()
        mLastTime = System.currentTimeMillis()
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
        if (mSaveFileMPUOutputs != null) {
            val uii4 = FileProvider.getUriForFile(context, context.packageName + ".provider", mSaveFileMPUOutputs!!.file)
            files.add(uii4)
        }
        if (mEcgHeartRespiratoryFile != null) {
            val uii5 = FileProvider.getUriForFile(context, context.packageName+".provider", mEcgHeartRespiratoryFile!!.file)
            files.add(uii5)
        }
        val exportData = Intent(Intent.ACTION_SEND_MULTIPLE)
        exportData.putExtra(Intent.EXTRA_SUBJECT, "ECG Sensor Data Export Details")
        exportData.putParcelableArrayListExtra(Intent.EXTRA_STREAM, files)
        exportData.type = "text/html"
        startActivity(exportData)
    }

    @Throws(IOException::class)
    private fun terminateDataFileWriter() {
        mPrimarySaveDataFile?.terminateDataFileWriter()
        mTensorflowOutputsSaveFile?.terminateDataFileWriter()
        mEcgHeartRespiratoryFile?.terminateDataFileWriter()
        mSaveFileMPU?.terminateDataFileWriter()
        mSaveFileMPUOutputs?.terminateDataFileWriter()
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
        val fileNameEcgHrrr = "ECG_HRRR_" + mTimeStamp + "_" + mSampleRate.toString() + "Hz"
        if (mEcgHeartRespiratoryFile == null) {
            Log.e(TAG, "fileTimeStamp: $fileNameEcgHrrr")
            mEcgHeartRespiratoryFile = SaveDataFile(directory2, fileNameEcgHrrr, 24, 2.0, saveTimestamps = false, includeClass = false)
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
        val fileNameTimeStamped2 = "MPUOutputs_$mTimeStamp"
        if (mSaveFileMPUOutputs == null) {
            mSaveFileMPUOutputs = SaveDataFile(directory, fileNameTimeStamped2, 16, 0.032, false, false)
        }
    }

    private fun setupGraph() {
        // 1. ECG Data Plot:
        mTimeDomainPlotAdapterCh1 = XYPlotAdapter(findViewById(R.id.ecgTimeDomainXYPlot), false, 2000)
        mGraphAdapterCh1 = GraphAdapter(2000, "ECG Data Ch 1", false, Color.BLUE)
        mTimeDomainPlotAdapterCh1?.xyPlot?.addSeries(mGraphAdapterCh1!!.series, mGraphAdapterCh1!!.lineAndPointFormatter)
        // 2. ECG Label Plot:
        mClassificationLabelsPlotAdapter = XYPlotAdapter(findViewById(R.id.ecgLabelXYPlot), false, 2000, "Time (s)", "Label")
        mClassificationLabelsPlotAdapter?.setRangeStepValue(1.0)
        mGraphAdapterClass0 = GraphAdapter(2000, "C0", false, Color.BLUE)
        mGraphAdapterClass1 = GraphAdapter(2000, "C1", false, Color.RED)
        mGraphAdapterClass2 = GraphAdapter(2000, "C2", false, Color.CYAN)
        mGraphAdapterClass3 = GraphAdapter(2000, "C3", false, Color.GREEN)
        mGraphAdapterClass4 = GraphAdapter(2000, "C4", false, Color.MAGENTA)
        mClassificationLabelsPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterClass0?.series, mGraphAdapterClass0?.lineAndPointFormatter)
        mClassificationLabelsPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterClass1?.series, mGraphAdapterClass1?.lineAndPointFormatter)
        mClassificationLabelsPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterClass2?.series, mGraphAdapterClass2?.lineAndPointFormatter)
        mClassificationLabelsPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterClass3?.series, mGraphAdapterClass3?.lineAndPointFormatter)
        mClassificationLabelsPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterClass4?.series, mGraphAdapterClass4?.lineAndPointFormatter)
        // 3. Motion Sensor Plot:
        mMotionDataPlotAdapter = XYPlotAdapter(findViewById(R.id.motionDataPlot), "Time (s)", "Acc (g)", 375.0)
        mGraphAdapterMotionAX = GraphAdapter(375, "Acc X", false, Color.RED)
        mGraphAdapterMotionAY = GraphAdapter(375, "Acc Y", false, Color.GREEN)
        mGraphAdapterMotionAZ = GraphAdapter(375, "Acc Z", false, Color.BLUE)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAX?.series, mGraphAdapterMotionAX?.lineAndPointFormatter)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAY?.series, mGraphAdapterMotionAY?.lineAndPointFormatter)
        mMotionDataPlotAdapter?.xyPlot!!.addSeries(mGraphAdapterMotionAZ?.series, mGraphAdapterMotionAZ?.lineAndPointFormatter)
        // 4. Start Redrawer:
        val xyPlotList = listOf(mTimeDomainPlotAdapterCh1?.xyPlot, mClassificationLabelsPlotAdapter?.xyPlot, mMotionDataPlotAdapter?.xyPlot)
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
        mGraphAdapterClass0!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterClass0?.setPointWidth(8f)
        mGraphAdapterClass1!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterClass1?.setPointWidth(8f)
        mGraphAdapterClass2!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterClass2?.setPointWidth(8f)
        mGraphAdapterClass3!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterClass3?.setPointWidth(8f)
        mGraphAdapterClass4!!.setxAxisIncrementFromSampleRate(mSampleRate)
        mGraphAdapterClass4?.setPointWidth(8f)
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
            mGraphAdapterCh1!!.plotData = chSel
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
                    mMPU = DataChannel(false, true, 0)
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
            mCh1 = DataChannel(false, mMSBFirst, 30 * mSampleRate)
            mCh2 = DataChannel(false, mMSBFirst, 30 * mSampleRate)
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
            mPrimarySaveDataFile!!.writeToDisk(mCh1!!.characteristicDataPacketBytes)
            // For every 2000 dp recieved, run classification model.
            if (mCh1!!.totalDataPointsReceived > 7500) {
                mHRRREnabled = true
            }
            if (mCh1!!.dataPointCounterClassify > 500 && mCh1!!.totalDataPointsReceived > 2000) {
                Log.e(TAG, "mClassifyThread Start Time")
                mCurrentIndex = mCh1!!.totalDataPointsReceived - 2000
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
            // TODO add data to it's own buffer (outside of mMPU) → (256, 6), as 6 sep arrays: use the following function to return relevant data(separated);
            addToGraphBufferMPU(mMPU!!)
            Log.e(TAG, "mMPU!!.totalDataPointsReceived: ${mMPU!!.totalDataPointsReceived}")
            if (mMPU!!.dataPointCounterClassify > 128 && mMPU!!.totalDataPointsReceived > 256) {
                Log.e(TAG, "mClassifyActivityThread Start Time")
                mMPU?.resetCounterClassify()
                val classifyActivityThread = Thread(mClassifyActivityThread)
                classifyActivityThread.start()
            }
            mSaveFileMPU!!.exportDataWithTimestampMPU(mMPU!!.characteristicDataPacketBytes)
            if (mSaveFileMPU!!.mLinesWrittenCurrentFile > 1048576) {
                mSaveFileMPU!!.terminateDataFileWriter()
                createNewFileMPU()
            }
        }
    }

    private fun addToGraphBuffer(graphAdapter: GraphAdapter, data: FloatArray, tStart: Int) {
        var t = tStart
        for (f in data) {
            graphAdapter.addDataPointTimeDomain(f.toDouble(), t)
            t += 1
        }
    }

    private fun addToGraphBufferMPU(dataChannel: DataChannel) {
        if (dataChannel.dataBuffer != null) {
            val numberDataPoints = dataChannel.dataBuffer!!.size / 12
            for (i in 0 until numberDataPoints) {
                val accX = DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i], dataChannel.dataBuffer!![12 * i + 1])
                val accY = DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i + 2], dataChannel.dataBuffer!![12 * i + 3])
                val accZ = DataChannel.bytesToDoubleMPUAccel(dataChannel.dataBuffer!![12 * i + 4], dataChannel.dataBuffer!![12 * i + 5])
                val gyrX = DataChannel.bytesToDoubleMPUGyro(dataChannel.dataBuffer!![12 * i + 6], dataChannel.dataBuffer!![12 * i + 7])
                val gyrY = DataChannel.bytesToDoubleMPUGyro(dataChannel.dataBuffer!![12 * i + 8], dataChannel.dataBuffer!![12 * i + 9])
                val gyrZ = DataChannel.bytesToDoubleMPUGyro(dataChannel.dataBuffer!![12 * i + 10], dataChannel.dataBuffer!![12 * i + 11])
                mGraphAdapterMotionAX?.addDataPointTimeDomain(accX, mTimestampIdxMPU)
                mGraphAdapterMotionAY?.addDataPointTimeDomain(accY, mTimestampIdxMPU)
                mGraphAdapterMotionAZ?.addDataPointTimeDomain(accZ, mTimestampIdxMPU)
                mTimestampIdxMPU += 1
                // Put in arrays: starting at back - numberDataPoints
                System.arraycopy(mAccXBuffer, 1, mAccXBuffer, 0, mAccXBuffer.size - 1) //shift backwards
                mAccXBuffer[255] = accX // Add to end
                System.arraycopy(mAccYBuffer, 1, mAccYBuffer, 0, mAccYBuffer.size - 1)
                mAccYBuffer[255] = accY
                System.arraycopy(mAccZBuffer, 1, mAccZBuffer, 0, mAccZBuffer.size - 1)
                mAccZBuffer[255] = accZ
                System.arraycopy(mGyrXBuffer, 1, mGyrXBuffer, 0, mGyrXBuffer.size - 1)
                mGyrXBuffer[255] = gyrX
                System.arraycopy(mGyrYBuffer, 1, mGyrYBuffer, 0, mGyrYBuffer.size - 1)
                mGyrYBuffer[255] = gyrY
                System.arraycopy(mGyrZBuffer, 1, mGyrZBuffer, 0, mGyrZBuffer.size - 1)
                mGyrZBuffer[255] = gyrZ
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

    private external fun jmainInitialization(initialize: Boolean): Int

    private external fun jecgFiltRescale(data: DoubleArray): FloatArray

    private external fun jactivPrep(data: DoubleArray): FloatArray

    private external fun jrearrange5c(data: FloatArray): FloatArray

    private external fun jgetClassDist(data: FloatArray): FloatArray

    // input/outputs: (2000, 5), as a (10000) array
    private external fun jreturnSmoothedLabels(data: FloatArray): FloatArray

    private external fun jGetHRRR(data_raw: DoubleArray): DoubleArray

    companion object {
        const val HZ = "0 Hz"
        private const val INPUT_DATA_FEED_KEY = "input_1"
        private const val OUTPUT_DATA_FEED_KEY = "conv1d_30/truediv"
        private const val INPUT_DATA_ACTIV_KEY = "conv1d_1_input"
        private const val OUTPUT_DATA_ACTIV_KEY = "dense_2/Softmax"
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
        private var mEcgHeartRespiratoryFile: SaveDataFile? = null
        private var mTensorflowOutputsSaveFile: SaveDataFile? = null
        private var mSaveFileMPU: SaveDataFile? = null
        private var mSaveFileMPUOutputs: SaveDataFile? = null

        init {
            System.loadLibrary("ecg-lib")
        }
    }
}
