#include <iostream>
#include <memory>

// using namespace std;
using std::cout;
using std::endl;
using std::shared_ptr;

typedef struct TestNum1
{
    int num;
}TestNum;


void foo1(std::shared_ptr<int>& val)
{
    std::shared_ptr<int> temp(val);
    *temp = 300;
}

void foo2(std::shared_ptr<int>& val)
{
    val = std::shared_ptr<int>(new int(200));
}

void test1()
{
    std::shared_ptr<int> val(new int(100));
    cout << "val=" << *val << endl;
    cout << "refs:" << val.use_count() << endl;
    foo1(val);
    cout << "val=" << *val << endl;
    cout << "refs:" << val.use_count() << endl;
    foo2(val);
    cout << "val=" << *val << endl;
    cout << "refs:" << val.use_count() << endl;
    cout << "--------" << endl;
}

void test2()
{
    shared_ptr<int> num(new int(1));
    cout << "num :" << num << endl;
    cout << "num addr:" << num.get() << endl;
    cout << "num val:" << *num << endl;
    cout << "--------" << endl;
    shared_ptr<int> nump;
    nump.reset(new int(2));
    // *nump = new int(2);
    cout << "num :" << nump << endl;
    cout << "num addr:" << nump.get() << endl;
    cout << "num val:" << *nump << endl;
    cout << "--------" << endl;
}

void test3()
{
    shared_ptr<TestNum> num;
    // num.reset(new TestNum);
    num = std::make_shared<TestNum>();
    num->num = 10;
    cout << "num :" << num << endl;
    cout << "num addr:" << num.get() << endl;
    cout << "num val:" << num->num << endl;
    cout << "--------" << endl;
}

void test4()
{
    std::shared_ptr<int> p1();
    std::cout << p1 << std::endl;
    std::shared_ptr<int> p2();
    std::cout << p2 << std::endl;
}
int main()
{
    test1();
    test2();
    test3();
    test4();
}


// AE配置信息：
// AEConfigInfoT configInfo;
// 这五项默认开启，硬终端有下发通道可以关闭，可能需要读取UI的配置
// configInfo.echoCancelMode = kAecModeEnabled/kAecModeDisabled; // AEC
// configInfo.echoSuppresionEnabled = 1/0; // AES
// configInfo.noiseSuppressEnabled = 1/0; // ANS
// configInfo.digitalAgcEnabled = 1/0; // AGC
// configInfo.drcEnabled  = 1/0; // DRC

// configInfo.initSpkMicDelayMs; // 初始延时，默认是0，根据后续测试情况，看是否需要设置高级音频诊断计算结果
// configInfo.timestampProcessEnabled = 1/0; // 是否启用时间戳处理，如果高级音频诊断结果提示有时钟漂移，需要启用
// configInfo.micFixedGain；// 固定增益，-20 ~ 20db，AGC disable情况下有效
// configInfo.spkHistoryLen = -1；// 回声路径长度，目前固定-1，使用AE默认值，后续可配置
// configInfo.longEchoLength = 1/0; // 是否使用长回声路径（会增加计算量），目前硬终端disable，DSP可配置，后续是否需要配置待定
// configInfo.arrayProcessMode；// 阵列处理方式，NE90为kArrayProcessModeBeamforming，其他终端为kArrayProcessModeBestMicSelect，
// configInfo.arrayProcessParam；// 阵列算法参数，arrayProcessMode为kArrayProcessModeBestMicSelect时，需要设置为-1；
// configInfo.beamformingMethod； // arrayProcessMode为kArrayProcessModeBeamforming时，设置为kBeamformingMethodDS
// configInfo.fbDelayMode；// filterbank延时模式，目前默认值kFilterBankMediumDelay，硬件终端可通过system property（persist.sys.audio.alg.fbd）配置
// configInfo.spkSampleRate；// 高级音频诊断得到时钟偏移对应的参考信号采样率，通过配置下发，影响timestampProcessEnabled设置
// configInfo.lowUsedBand = 100; // 信号有效频谱下限，目前固定100Hz
// configInfo.highUsedBand = 20000; // 信号有效频谱上限，目前固定12000Hz
// configInfo.streamAlignMode；// 信号对齐检测方式，NE90为kStreamAlignModeAdapiveFilterOnce，ME60为kStreamAlignModeAdapiveFilter

// configInfo.sampleRate；// 采样率，固定值48000
// configInfo.frameLen；// 帧长，单位毫秒
// configInfo.loggingPath；// AE内部dump数据保存路径，设置的同时在该文件夹放置aelog.config配置文件，可以开启dump，软终端目前使用的dump数据方式
// configInfo.configPath; // AE内部保存上次呼叫mic/spk实际延时的文件路径，可以同loggingPath，设置后，下次呼叫会读取该文件并设置初始延时
