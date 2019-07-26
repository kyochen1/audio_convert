// test-audio-convert.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <string>
#include <wtypes.h>
#include <audio_convert.h>
#include <audio_convert.cpp>

using namespace netinfo;

std::string get_run_path(void) 
{
	char run_path[MAX_PATH] = { 0 };
	::GetModuleFileNameA(NULL, run_path, MAX_PATH);
	char *pos = strrchr(run_path, '\\');
	*(pos + 1) = '\0';
	return run_path;
}



int main()
{ 
	std::string run_path = get_run_path();
	
	audio_convert ac;
	wav_header wh;

	// 获取wav头信息
	int ret = ac.read_wav_header((run_path + "\\wav\\pcm16_mono.wav").c_str(), &wh);
	unsigned int length = wh.length();

	// 单声道转双声道
// 	ret = ac.wav_mono_to_stereo(
// 		(run_path + "\\wav\\pcm16_mono.wav").c_str(), 
// 		(run_path + "\\wav\\pcm16_mono_1.wav").c_str());

 	// 双声道转单声道
// 	ret = ac.wav_stereo_to_mono(
// 		(run_path + "\\wav\\ulaw_stereo.wav").c_str(),
// 		(run_path + "\\wav\\ulaw_stereo_1.wav").c_str());

 	// 双声道分离
// 	ret = ac.wav_stereo_to_split(
// 		(run_path + "\\wav\\pcm16_stereo.wav").c_str(),
// 		(run_path + "\\wav\\pcm16_stereo_l.wav").c_str(),
// 		(run_path + "\\wav\\pcm16_stereo_r.wav").c_str());

	// 双声道合并
// 	ret = ac.wav_stereo_to_merge(
// 		(run_path + "\\wav\\pcm16_mono.wav").c_str(),
// 		(run_path + "\\wav\\pcm16_v3.wav").c_str(),
// 		(run_path + "\\wav\\pcm16_stereo_m.wav").c_str());

	// PCM8（alaw和ulaw）转PCM16
// 	ret = ac.wav_pcm8_to_pcm16(
// 		(run_path + "\\wav\\ulaw_stereo.wav").c_str(),
// 		(run_path + "\\wav\\ulaw_stereo_16.wav").c_str());
	
	// PCM16转PCM8（alaw和ulaw）
// 	ret = ac.wav_pcm16_to_pcm8(
// 		(run_path + "\\wav\\pcm16_stereo.wav").c_str(),
// 		(run_path + "\\wav\\pcm16_stereo_u.wav").c_str(), WAV_FORMAT_G711U);


	return 0;
}
