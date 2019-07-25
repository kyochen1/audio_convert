#pragma once

namespace netinfo {

	const unsigned short WAV_FORMAT_PCM = 1;			// PCM
	const unsigned short WAV_FORMAT_MSADPCM = 2;		// Microsoft ADPCM 
	const unsigned short WAV_FORMAT_G711A = 6;			// ITU G.711 a-law
	const unsigned short WAV_FORMAT_G711U = 7;			// ITU G.711 µ-law
	const unsigned short WAV_FORMAT_IMAADPCM = 17;		// IMA ADPCM
	const unsigned short WAV_FORMAT_G723 = 20;			// ITU G.723 ADPCM
	const unsigned short WAV_FORMAT_GSM = 49;			// GSM 6.10
	const unsigned short WAV_FORMAT_G721 = 64;			// ITU G.721 ADPCM

	struct wav_header {

		wav_header(void);

		wav_header(const wav_header &r);
		
		wav_header& operator=(const wav_header &r);
		
		~wav_header(void);

		void init(void);
		
		void init_pcm8(void);

		void init_pcm16(void);
		
		void clear();
		
		unsigned int length(void);

#pragma region RIFF头
		// RIFF标识
		char riff_name[4];
		// 去掉RIFF头后字节数
		unsigned int riff_length;
#pragma endregion

#pragma region 数据类型标识
		// 数据类型标识
		char wav_name[4];
#pragma endregion

#pragma region 格式块中的块头
		// 格式标识
		char fmt_name[4];
		// 格式块大小
		unsigned int fmt_length;
#pragma endregion

#pragma region 格式块中的数据
		// 音频格式
		unsigned short audio_format;
		// 声道数量
		unsigned short channels;
		// 采样率
		unsigned int sample_rate;
		// 每秒采样字节数，其值 = sample_rate * (bits_per_sample / 8) * channel_number
		unsigned int bytes_per_second;
		// 每次采样字节数，其值 = bits_per_sample * channel_number / 8
		unsigned short bytes_per_sample;
		// 每个声道的采样精度
		unsigned short bits_per_sample;
#pragma endregion

#pragma region 附加信息（可选），根据fmt_length判断
		// 扩展域大小
		unsigned short append_message;
		// 扩展域信息
		char *append_message_data;
#pragma endregion

#pragma region Fact块(可选)，一般当wav文件由某些软件转化而成，则包含该Chunk
		// fact标识
		char fact_name[4];
		// fact长度
		unsigned int fact_length;
		// fact数据
		char* fact_data;
#pragma endregion

#pragma region 音频数据
		// 数据标识
		char data_name[4];
		// 数据长度
		unsigned int data_length;
#pragma endregion
	};

	class audio_convert {
	public:
		// 读取WAV头信息
		int read_wav_header(const char* const src_filename, wav_header* const p_wav_header);
		// 写入WAV头信息
		int write_wav_header(const char* const dst_filename, const wav_header* const p_wav_header, const bool );
	
		// PCM单字节单声道数据转换双声道（dst_data需要手动清理）
		int pcm_mono_to_stereo(const char* const src_data, const unsigned int src_size
			, char** const dst_data, unsigned int* const dst_size);
		// PCM双字节单声道数据转换双声道（dst_data需要手动清理）
		int pcm_mono_to_stereo(const short* const src_data, const unsigned int src_size
			, short** const dst_data, unsigned int* const dst_size);
		// WAV文件单声道转双声道（只支持PCM,PCMA和PCMU）
		int wav_mono_to_stereo(const char* const src_filename, const char* const dst_filename);

		// PCM单字节双声道数据转换单声道（dst_data需要手动清理）
		int pcm_stereo_to_mono(const char* const src_data, const unsigned int src_size
			, char** const dst_data, unsigned int* const dst_size, const unsigned short format=WAV_FORMAT_PCM);
		// PCM双字节双声道数据转换单声道（dst_data需要手动清理）
		int pcm_stereo_to_mono(const short* const src_data, const unsigned int src_size
			, short** const dst_data, unsigned int* const dst_size);
		// WAV文件双声道转单声道（只支持PCM, 待完成PCMA和PCMU）
		int wav_stereo_to_mono(const char* const src_filename, const char* const dst_filename);

		// PCM单字节双声道数据分离（left_data，right_data需要手动清理）
		int pcm_stereo_to_split(const char * const src_data, const unsigned int src_size
			, char** const left_data, unsigned int* const left_size
			, char** const right_data, unsigned int* const right_size);
		// PCM单字节双声道数据分离（left_data，right_data需要手动清理）
		int pcm_stereo_to_split(const short * const src_data, const unsigned int src_size
			, short** const left_data, unsigned int* const left_size
			, short** const right_data, unsigned int* const right_size);
		// WAV文件双声道分离（只支持PCM,PCMA和PCMU）
		int wav_stereo_to_split(const char* const src_filename
			, const char* const left_filename, const char* const right_filename);

		// PCM单字节左右声道数据合成（dst_data需要手动清理）
		int pcm_stereo_to_merge(const char* const left_data, const unsigned int left_size
			, const char* const right_data, const unsigned int right_size
			, char** const dst_data, unsigned int* const dst_size, const unsigned short format=WAV_FORMAT_PCM);
		// PCM单字节左右声道数据合成（dst_data需要手动清理）
		int pcm_stereo_to_merge(const short* const left_data, const unsigned int left_size
			, const short* const right_data, const unsigned int right_size
			, short** const dst_data, unsigned int* const dst_size);
		// WAV文件左右声道合成（只支持PCM,PCMA和PCMU）
		int wav_stereo_to_merge(const char* const left_filename
			, const char* const right_filename, const char* const dst_filename);

		// PCM8数据转换PCM16数据（dst_data需要手动清理）
		int pcm8_to_pcm16(const char* const src_data, const unsigned int src_size
			, short** const dst_data, unsigned int* const dst_size);
		// WAV文件PCM8转换PCM16
		int wav_pcm8_to_pcm16(const char* const src_filename, const char* const dst_filename);

		// PCM16数据转换PCM8数据（dst_data需要手动清理）
		int pcm16_to_pcm8(const short* const src_data, const unsigned int src_size
			, char** const dst_data, unsigned int* const dst_size);
		// WAV文件PCM16转PCM8
		int wav_pcm16_to_pcm8(const char* const src_filename, const char* const dst_filename);

		// ALAW和ULAW待完善

	private:
		
	};

}