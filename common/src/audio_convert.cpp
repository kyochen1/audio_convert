#include <cstring>
#include <cstdio>
#include <winerror.h>
#include "audio_convert.h"

namespace netinfo {

	wav_header::wav_header(void) {
		init();
	}

	wav_header::wav_header(const wav_header &r) {
		init();
		*this = r;
	}

	wav_header& wav_header::operator=(const wav_header &r) {
		memcpy(riff_name, r.riff_name, sizeof(riff_name));
		riff_length = r.riff_length;

		memcpy(wav_name, r.wav_name, sizeof(wav_name));

		memcpy(fmt_name, r.fmt_name, sizeof(fmt_name));
		fmt_length = r.fmt_length;

		audio_format = r.audio_format;
		channels = r.channels;
		sample_rate = r.sample_rate;
		bytes_per_second = r.bytes_per_second;
		bytes_per_sample = r.bytes_per_sample;
		bits_per_sample = r.bits_per_sample;

		append_message = r.append_message;
		if (append_message_data != nullptr) {
			delete[] append_message_data;
			append_message_data = nullptr;
		}
		if (r.append_message != 0 && r.append_message_data != nullptr) {
			append_message_data = new char[r.append_message];
			memcpy(append_message_data, r.append_message_data, append_message);
		}

		memcpy(fact_name, r.fact_name, sizeof(fact_name));
		fact_length = r.fact_length;
		if (fact_data != nullptr) {
			delete[] fact_data;
			fact_data = nullptr;
		}
		if (r.fact_length != 0 && r.fact_data != nullptr) {
			fact_data = new char[r.fact_length];
			memcpy(fact_data, r.fact_data, fact_length);
		}
		memcpy(data_name, r.data_name, sizeof(data_name));
		data_length = r.data_length;

		return *this;
	}

	wav_header::~wav_header(void) {
		if (append_message_data != nullptr) {
			delete[] append_message_data;
			append_message_data = nullptr;
		}
		if (fact_data != nullptr) {
			delete[] fact_data;
			fact_data = nullptr;
		}
	}

	void wav_header::init(void) {
		memset(riff_name, 0, sizeof(riff_name));
		riff_length = 0;

		memset(wav_name, 0, sizeof(wav_name));

		memset(fmt_name, 0, sizeof(fmt_name));
		fmt_length = 0;

		audio_format = 0;
		channels = 0;
		sample_rate = 0;
		bytes_per_second = 0;
		bytes_per_sample = 0;
		bits_per_sample = 0;

		append_message = 0;
		append_message_data = nullptr;

		memset(fact_name, 0, sizeof(fact_name));
		fact_length = 0;
		fact_data = nullptr;

		memset(data_name, 0, sizeof(data_name));
		data_length = 0;
	}

	void wav_header::clear() {
		memset(riff_name, 0, sizeof(riff_name));
		riff_length = 0;

		memset(wav_name, 0, sizeof(wav_name));

		memset(fmt_name, 0, sizeof(fmt_name));
		fmt_length = 0;

		audio_format = 0;
		channels = 0;
		sample_rate = 0;
		bytes_per_second = 0;
		bytes_per_sample = 0;
		bits_per_sample = 0;

		append_message = 0;
		if (append_message_data != nullptr) {
			delete[] append_message_data;
			append_message_data = nullptr;
		}

		memset(fact_name, 0, sizeof(fact_name));
		fact_length = 0;
		if (fact_data != nullptr) {
			delete[] fact_data;
			fact_data = nullptr;
		}

		memset(data_name, 0, sizeof(data_name));
		data_length = 0;
	}

	void wav_header::init_pcm8(void) {
		riff_name[0] = 'R';
		riff_name[1] = 'I';
		riff_name[2] = 'F';
		riff_name[3] = 'F';
		riff_length = 0;

		wav_name[0] = 'W';
		wav_name[1] = 'A';
		wav_name[2] = 'V';
		wav_name[3] = 'E';

		fmt_name[0] = 'f';
		fmt_name[1] = 'm';
		fmt_name[2] = 't';
		fmt_name[3] = ' ';
		fmt_length = 16;

		audio_format = WAV_FORMAT_PCM;
		channels = 1;
		sample_rate = 8000;
		bytes_per_second = 8000;
		bytes_per_sample = 1;
		bits_per_sample = 8;

		append_message = 0;
		if (append_message_data != nullptr) {
			delete[] append_message_data;
			append_message_data = nullptr;
		}

		fact_name[0] = 0;
		fact_name[1] = 0;
		fact_name[2] = 0;
		fact_name[3] = 0;
		fact_length = 0;
		if (fact_data != nullptr) {
			delete[] fact_data;
			fact_data = nullptr;
		}

		data_name[0] = 'd';
		data_name[1] = 'a';
		data_name[2] = 't';
		data_name[3] = 'a';
		data_length = 0;
	}

	void wav_header::init_pcm16(void) {
		riff_name[0] = 'R';
		riff_name[1] = 'I';
		riff_name[2] = 'F';
		riff_name[3] = 'F';
		riff_length = 0;

		wav_name[0] = 'W';
		wav_name[1] = 'A';
		wav_name[2] = 'V';
		wav_name[3] = 'E';

		fmt_name[0] = 'f';
		fmt_name[1] = 'm';
		fmt_name[2] = 't';
		fmt_name[3] = ' ';
		fmt_length = 16;

		audio_format = WAV_FORMAT_PCM;
		channels = 1;
		sample_rate = 8000;
		bytes_per_second = 16000;
		bytes_per_sample = 2;
		bits_per_sample = 16;

		append_message = 0;
		if (append_message_data != nullptr) {
			delete[] append_message_data;
			append_message_data = nullptr;
		}

		fact_name[0] = 0;
		fact_name[1] = 0;
		fact_name[2] = 0;
		fact_name[3] = 0;
		fact_length = 0;
		if (fact_data != nullptr) {
			delete[] fact_data;
			fact_data = nullptr;
		}

		data_name[0] = 'd';
		data_name[1] = 'a';
		data_name[2] = 't';
		data_name[3] = 'a';
		data_length = 0;
	}

	unsigned int wav_header::length(void) {
		int length = 28 + fmt_length;
		if (memcmp(fact_name, "fact", sizeof(fact_name)) == 0) {
			length += 8 + fact_length;
		}
		return length;
	}

	int audio_convert::read_wav_header(const char* const src_filename, wav_header* const p_wav_header) {
		if (p_wav_header == nullptr) {
			return ERROR_INVALID_BLOCK;
		}
		p_wav_header->clear();

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		int size = sizeof(p_wav_header->riff_name);
		if (fread(p_wav_header->riff_name, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->riff_length);
		if (fread(&p_wav_header->riff_length, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->wav_name);
		if (fread(p_wav_header->wav_name, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->fmt_name);
		if (fread(p_wav_header->fmt_name, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->fmt_length);
		if (fread(&p_wav_header->fmt_length, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->audio_format);
		if (fread(&p_wav_header->audio_format, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->channels);
		if (fread(&p_wav_header->channels, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->sample_rate);
		if (fread(&p_wav_header->sample_rate, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bytes_per_second);
		if (fread(&p_wav_header->bytes_per_second, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bytes_per_sample);
		if (fread(&p_wav_header->bytes_per_sample, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bits_per_sample);
		if (fread(&p_wav_header->bits_per_sample, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		if (p_wav_header->fmt_length >= 18) {
			size = sizeof(p_wav_header->append_message);
			if (fread(&p_wav_header->append_message, 1, size, src_file) != size) {
				fclose(src_file);
				return ERROR_INVALID_DATA;
			}

			if (p_wav_header->append_message > 0) {
				size = p_wav_header->append_message;
				p_wav_header->append_message_data = new char[size];
				if (fread(p_wav_header->append_message_data, 1, size, src_file) != size) {
					fclose(src_file);
					return ERROR_INVALID_DATA;
				}
			}
		}

		char chunk_name[4];
		size = sizeof(chunk_name);
		if (fread(chunk_name, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		if (memcmp(chunk_name, "fact", sizeof(chunk_name)) == 0) {
			memcpy(p_wav_header->fact_name, chunk_name, sizeof(p_wav_header->fact_name));

			size = sizeof(p_wav_header->fact_length);
			if (fread(&p_wav_header->fact_length, 1, size, src_file) != size) {
				fclose(src_file);
				return ERROR_INVALID_DATA;
			}

			size = p_wav_header->fact_length;
			p_wav_header->fact_data = new char[size];
			if (fread(p_wav_header->fact_data, 1, size, src_file) != size) {
				fclose(src_file);
				return ERROR_INVALID_DATA;
			}

			size = sizeof(p_wav_header->data_name);
			if (fread(p_wav_header->data_name, 1, size, src_file) != size) {
				fclose(src_file);
				return ERROR_INVALID_DATA;
			}
		}
		else {
			memcpy(p_wav_header->data_name, chunk_name, sizeof(p_wav_header->data_name));
		}

		size = sizeof(p_wav_header->data_length);
		if (fread(&p_wav_header->data_length, 1, size, src_file) != size) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}
		fclose(src_file);
		return ERROR_SUCCESS;
	}

	int audio_convert::write_wav_header(
		const char* const dst_filename, const wav_header* const p_wav_header, const bool is_create) {
		if (p_wav_header == nullptr) {
			return ERROR_INVALID_BLOCK;
		}

		FILE *dst_file = nullptr;
		if (is_create) {
			dst_file = fopen(dst_filename, "wb");
		}
		else {
			dst_file = fopen(dst_filename, "rb+");
		}

		if (dst_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		int size = sizeof(p_wav_header->riff_name);
		if (fwrite(p_wav_header->riff_name, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->riff_length);
		if (fwrite(&p_wav_header->riff_length, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->wav_name);
		if (fwrite(p_wav_header->wav_name, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->fmt_name);
		if (fwrite(p_wav_header->fmt_name, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->fmt_length);
		if (fwrite(&p_wav_header->fmt_length, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->audio_format);
		if (fwrite(&p_wav_header->audio_format, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->channels);
		if (fwrite(&p_wav_header->channels, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->sample_rate);
		if (fwrite(&p_wav_header->sample_rate, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bytes_per_second);
		if (fwrite(&p_wav_header->bytes_per_second, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bytes_per_sample);
		if (fwrite(&p_wav_header->bytes_per_sample, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->bits_per_sample);
		if (fwrite(&p_wav_header->bits_per_sample, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		if (p_wav_header->fmt_length >= 18) {
			size = sizeof(p_wav_header->append_message);
			if (fwrite(&p_wav_header->append_message, 1, size, dst_file) != size) {
				fclose(dst_file);
				return ERROR_INVALID_DATA;
			}
			if (p_wav_header->append_message > 0) {
				size = p_wav_header->append_message;
				if (fwrite(p_wav_header->append_message_data, 1, size, dst_file) != size) {
					fclose(dst_file);
					return ERROR_INVALID_DATA;
				}
			}
		}

		if (memcmp(p_wav_header->fact_name, "fact", sizeof(p_wav_header->fact_name)) == 0) {
			size = sizeof(p_wav_header->fact_name);
			if (fwrite(p_wav_header->fact_name, 1, size, dst_file) != size) {
				fclose(dst_file);
				return ERROR_INVALID_DATA;
			}

			size = sizeof(p_wav_header->fact_length);
			if (fwrite(&p_wav_header->fact_length, 1, size, dst_file) != size) {
				fclose(dst_file);
				return ERROR_INVALID_DATA;
			}

			size = p_wav_header->fact_length;
			if (fwrite(p_wav_header->fact_data, 1, size, dst_file) != size) {
				fclose(dst_file);
				return ERROR_INVALID_DATA;
			}
		}

		size = sizeof(p_wav_header->data_name);
		if (fwrite(p_wav_header->data_name, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}

		size = sizeof(p_wav_header->data_length);
		if (fwrite(&p_wav_header->data_length, 1, size, dst_file) != size) {
			fclose(dst_file);
			return ERROR_INVALID_DATA;
		}
		fclose(dst_file);
		return ERROR_SUCCESS;
	}

	int audio_convert::pcm_mono_to_stereo(
		const char* const src_data, const unsigned int src_size
		, char** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = src_size;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples * 2;
		*dst_data = new char[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[2 * i] = src_data[i];
			(*dst_data)[2 * i + 1] = src_data[i];
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::pcm_mono_to_stereo(
		const short* const src_data, const unsigned int src_size
		, short** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = src_size;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples * 2;
		*dst_data = new short[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[2 * i] = src_data[i];
			(*dst_data)[2 * i + 1] = src_data[i];
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_mono_to_stereo(
		const char* const src_filename, const char* const dst_filename) {
		wav_header src_wh;
		int ret = read_wav_header(src_filename, &src_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (src_wh.audio_format != WAV_FORMAT_PCM
			&& src_wh.audio_format != WAV_FORMAT_G711A
			&& src_wh.audio_format != WAV_FORMAT_G711U) {
			return ERROR_NOT_SUPPORTED;
		}
		if (src_wh.channels != 1) {
			return ERROR_INVALID_DATA;
		}

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(src_file, src_wh.length(), 0);
		if (ret != 0) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		wav_header dst_wh;
		if (src_wh.bits_per_sample == 8) {
			dst_wh.init_pcm8();
			dst_wh.audio_format = src_wh.audio_format;
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 16000;
			dst_wh.bytes_per_sample = 2;
		}
		else {
			dst_wh.init_pcm16();
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 32000;
			dst_wh.bytes_per_sample = 4;
		}

		ret = write_wav_header(dst_filename, &dst_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		FILE *dst_file = fopen(dst_filename, "ab");
		if (dst_file == nullptr) {
			fclose(src_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		if (src_wh.bits_per_sample == 8) {
			char src_data[128] = { 0 };
			char *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int size = fread(src_data, 1, 128, src_file);
				if (size * 2 + data_length >= src_wh.data_length * 2) {
					size = src_wh.data_length - data_length / 2;
				}
				if (size == 0) {
					break;
				}

				if (pcm_mono_to_stereo(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 1, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size;
			}
		}
		else {
			short src_data[128] = { 0 };
			short *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int size = fread(src_data, 2, 128, src_file);
				if (size * 2 * 2 + data_length >= src_wh.data_length * 2) {
					size = (src_wh.data_length - data_length / 2) / 2;
				}
				if (size == 0) {
					break;
				}

				if (pcm_mono_to_stereo(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 2, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size * 2;
			}
		}
		fclose(src_file);
		fclose(dst_file);

		dst_wh.data_length = data_length;
		dst_wh.riff_length = data_length + dst_wh.length() - 8;
		return write_wav_header(dst_filename, &dst_wh, false);
	}

	int audio_convert::pcm_stereo_to_mono(
		const char* const src_data, const unsigned int src_size
		, char** const dst_data, unsigned int* const dst_size, const unsigned short format) {
		unsigned int samples = src_size / 2;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples;
		*dst_data = new char[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[i] = ((int)src_data[2 * i] + (int)src_data[2 * i + 1]) >> 1;
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::pcm_stereo_to_mono(
		const short* const src_data, const unsigned int src_size
		, short** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = src_size / 2;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples;
		*dst_data = new short[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[i] = ((int)src_data[2 * i] + (int)src_data[2 * i + 1]) >> 1;
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_stereo_to_mono(
		const char* const src_filename, const char* const dst_filename) {
		wav_header src_wh;
		int ret = read_wav_header(src_filename, &src_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (src_wh.audio_format != WAV_FORMAT_PCM) {
			return ERROR_NOT_SUPPORTED;
		}
		if (src_wh.channels != 2) {
			return ERROR_INVALID_DATA;
		}

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(src_file, src_wh.length(), 0);
		if (ret != 0) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		wav_header dst_wh;
		if (src_wh.bits_per_sample == 8) {
			dst_wh.init_pcm8();
		}
		else {
			dst_wh.init_pcm16();
		}

		ret = write_wav_header(dst_filename, &dst_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		FILE *dst_file = fopen(dst_filename, "ab");
		if (dst_file == nullptr) {
			fclose(src_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		if (src_wh.bits_per_sample == 8) {
			char src_data[128] = { 0 };
			char *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int size = fread(src_data, 1, 128, src_file);
				if (size / 2 + data_length >= src_wh.data_length / 2) {
					size = src_wh.data_length - data_length * 2;
				}
				if (size == 0) {
					break;
				}
				if (pcm_stereo_to_mono(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 1, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size;
			}
		}
		else {
			short src_data[128] = { 0 };
			short *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int size = fread(src_data, 2, 128, src_file);
				if (size + data_length >= src_wh.data_length / 2) {
					size = src_wh.data_length / 2 - data_length;
				}
				if (size == 0) {
					break;
				}
				if (pcm_stereo_to_mono(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 2, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size * 2;
			}
		}
		fclose(src_file);
		fclose(dst_file);

		dst_wh.data_length = data_length;
		dst_wh.riff_length = data_length + dst_wh.length() - 8;
		return write_wav_header(dst_filename, &dst_wh, false);
	}

	int audio_convert::pcm_stereo_to_split(
		const char * const src_data, const unsigned int src_size
		, char** const left_data, unsigned int* const left_size
		, char** const right_data, unsigned int* const right_size) {
		unsigned int samples = src_size / 2;
		if (src_data == nullptr || samples == 0 
			|| left_data == nullptr || left_size == nullptr
			|| right_data == nullptr || right_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*left_size = samples;
		*left_data = new char[*left_size];
		*right_size = samples;
		*right_data = new char[*right_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*left_data)[i] = src_data[2 * i];
			(*right_data)[i] = src_data[2 * i + 1];
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::pcm_stereo_to_split(
		const short * const src_data, const unsigned int src_size
		, short** const left_data, unsigned int* const left_size
		, short** const right_data, unsigned int* const right_size) {
		unsigned int samples = src_size / 2;
		if (src_data == nullptr || samples == 0
			|| left_data == nullptr || left_size == nullptr
			|| right_data == nullptr || right_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*left_size = samples;
		*left_data = new short[*left_size];
		*right_size = samples;
		*right_data = new short[*right_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*left_data)[i] = src_data[2 * i];
			(*right_data)[i] = src_data[2 * i + 1];
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_stereo_to_split(const char* const src_filename
		, const char* const left_filename, const char* const right_filename) {
		wav_header src_wh;
		int ret = read_wav_header(src_filename, &src_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (src_wh.audio_format != WAV_FORMAT_PCM
			&& src_wh.audio_format != WAV_FORMAT_G711A
			&& src_wh.audio_format != WAV_FORMAT_G711U) {
			return ERROR_NOT_SUPPORTED;
		}
		if (src_wh.channels != 2) {
			return ERROR_INVALID_DATA;
		}

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(src_file, src_wh.length(), 0);
		if (ret != 0) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		wav_header left_wh;
		wav_header right_wh;
		if (src_wh.bits_per_sample == 8) {
			left_wh.init_pcm8();
			left_wh.audio_format = src_wh.audio_format;
			right_wh.init_pcm8();
			right_wh.audio_format = src_wh.audio_format;
		}
		else {
			left_wh.init_pcm16();
			right_wh.init_pcm16();
		}

		ret = write_wav_header(left_filename, &left_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		ret = write_wav_header(right_filename, &right_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		FILE *left_file = fopen(left_filename, "ab");
		if (left_file == nullptr) {
			fclose(src_file);
			return ERROR_FILE_NOT_FOUND;
		}
		
		FILE *right_file = fopen(right_filename, "ab");
		if (right_file == nullptr) {
			fclose(src_file);
			fclose(left_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		if (src_wh.bits_per_sample == 8) {
			char src_data[128] = { 0 };
			char *left_data = nullptr;
			unsigned int left_size = 0;
			char *right_data = nullptr;
			unsigned int right_size = 0;
			
			while (true) {				
				unsigned int size = fread(src_data, 1, 128, src_file);
				if (size / 2 + data_length >= src_wh.data_length / 2) {
					size = src_wh.data_length - data_length * 2;
				}
				if (size == 0) {
					break;
				}

				if (pcm_stereo_to_split(src_data, size
					, &left_data, &left_size, &right_data, &right_size) != ERROR_SUCCESS) {
					break;
				}

				if (fwrite(left_data, 1, left_size, left_file) != left_size) {
					delete[] left_data;
					delete[] right_data;
					break;
				}

				if (fwrite(right_data, 1, right_size, right_file) != right_size) {
					delete[] left_data;
					delete[] right_data;
					break;
				}

				delete[] left_data;
				delete[] right_data;
				data_length += left_size;
			}
		}
		else {
			short src_data[128] = { 0 };
			short *left_data = nullptr;
			unsigned int left_size = 0;
			short *right_data = nullptr;
			unsigned int right_size = 0;

			while (true) {
				unsigned int size = fread(src_data, 2, 128, src_file);
				if (size + data_length >= src_wh.data_length / 2) {
					size = src_wh.data_length / 2 - data_length;
				}
				if (size == 0) {
					break;
				}

				if (pcm_stereo_to_split(src_data, size
					, &left_data, &left_size, &right_data, &right_size) != ERROR_SUCCESS) {
					break;
				}

				if (fwrite(left_data, 2, left_size, left_file) != left_size) {
					delete[] left_data;
					delete[] right_data;
					break;
				}

				if (fwrite(right_data, 2, right_size, right_file) != right_size) {
					delete[] left_data;
					delete[] right_data;
					break;
				}
				delete[] left_data;
				delete[] right_data;
				data_length += left_size * 2;
			}
		}
		fclose(src_file);
		fclose(left_file);
		fclose(right_file);

		left_wh.data_length = data_length;
		left_wh.riff_length = data_length + left_wh.length() - 8;
		ret = write_wav_header(left_filename, &left_wh, false);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		right_wh.data_length = data_length;
		right_wh.riff_length = data_length + right_wh.length() - 8;
		return write_wav_header(right_filename, &right_wh, false);
	}

	int audio_convert::pcm_stereo_to_merge(
		const char* const left_data, const unsigned int left_size
		, const char* const right_data, const unsigned int right_size
		, char** const dst_data, unsigned int* const dst_size, const unsigned short format) {
		unsigned int samples = max(left_size, right_size);
		if ((left_data == nullptr && right_data == nullptr)
			|| samples == 0
			|| (left_size != 0 && left_data == nullptr)
			|| (right_size != 0 && right_data == nullptr)
			|| dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples * 2;
		*dst_data = new char[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			if (i < left_size) {
				(*dst_data)[2 * i] = left_data[i];
			}
			else {
				if (format == WAV_FORMAT_G711A) {
					(*dst_data)[2 * i] = (char)0xD5;
				} 
				else if (format == WAV_FORMAT_G711U) {
					(*dst_data)[2 * i] = (char)0xFF;
				}
				else {
					(*dst_data)[2 * i] = (char)0x80;
				}
			}
			if (i < right_size) {
				(*dst_data)[2 * i + 1] = right_data[i];
			}
			else {
				if (format == WAV_FORMAT_G711A) {
					(*dst_data)[2 * i + 1] = (char)0xD5;
				}
				else if (format == WAV_FORMAT_G711U) {
					(*dst_data)[2 * i + 1] = (char)0xFF;
				}
				else {
					(*dst_data)[2 * i + 1] = (char)0x80;
				}
			}
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::pcm_stereo_to_merge(
		const short* const left_data, const unsigned int left_size
		, const short* const right_data, const unsigned int right_size
		, short** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = max(left_size, right_size);
		if ((left_data == nullptr && right_data == nullptr)
			|| samples == 0
			|| (left_size != 0 && left_data == nullptr)
			|| (right_size != 0 && right_data == nullptr)
			|| dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples * 2;
		*dst_data = new short[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			if (i < left_size) {
				(*dst_data)[2 * i] = left_data[i];
			}
			else {
				(*dst_data)[2 * i] = 0;
			}
			if (i < right_size) {
				(*dst_data)[2 * i + 1] = right_data[i];
			}
			else {
				(*dst_data)[2 * i + 1] = 0;
			}
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_stereo_to_merge(const char* const left_filename
		, const char* const right_filename, const char* const dst_filename) {
		wav_header left_wh;
		wav_header right_wh;
		int ret = read_wav_header(left_filename, &left_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		ret = read_wav_header(right_filename, &right_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (left_wh.audio_format != right_wh.audio_format
			|| left_wh.bits_per_sample != right_wh.bits_per_sample
			|| left_wh.channels != 1 || right_wh.channels != 1) {
			return ERROR_INVALID_DATA;
		}

		if (left_wh.audio_format != WAV_FORMAT_PCM
			&& left_wh.audio_format != WAV_FORMAT_G711A
			&& left_wh.audio_format != WAV_FORMAT_G711U) {
			return ERROR_NOT_SUPPORTED;
		}

		FILE *left_file = fopen(left_filename, "rb");
		if (left_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		FILE *right_file = fopen(right_filename, "rb");
		if (right_file == nullptr) {
			fclose(left_file);
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(left_file, left_wh.length(), 0);
		if (ret != 0) {
			fclose(left_file);
			fclose(right_file);
			return ERROR_INVALID_DATA;
		}

		ret = fseek(right_file, right_wh.length(), 0);
		if (ret != 0) {
			fclose(left_file);
			fclose(right_file);
			return ERROR_INVALID_DATA;
		}

		wav_header dst_wh;
		if (left_wh.bits_per_sample == 8) {
			dst_wh.init_pcm8();
			dst_wh.audio_format = left_wh.audio_format;
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 16000;
			dst_wh.bytes_per_sample = 2;
		}
		else {
			dst_wh.init_pcm16();
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 32000;
			dst_wh.bytes_per_sample = 4;
		}

		ret = write_wav_header(dst_filename, &dst_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(left_file);
			fclose(right_file);
			return ret;
		}

		FILE *dst_file = fopen(dst_filename, "ab");
		if (dst_file == nullptr) {
			fclose(left_file);
			fclose(right_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		if (dst_wh.bits_per_sample == 8) {
			char left_data[128] = { 0 };
			char right_data[128] = { 0 };
			char *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int left_size = fread(left_data, 1, 128, left_file);
				unsigned int right_size = fread(right_data, 1, 128, right_file);

				if (left_size * 2 + data_length >= left_wh.data_length * 2) {
					left_size = left_wh.data_length - data_length / 2;
				}
				if (right_size * 2 + data_length >= right_wh.data_length * 2) {
					right_size = right_wh.data_length - data_length / 2;
				}
				if (data_length >= left_wh.data_length * 2) {
					left_size = 0;
				}
				if (data_length >= right_wh.data_length * 2) {
					right_size = 0;
				}
				if (left_size == 0 && right_size == 0) {
					break;
				}

				if (pcm_stereo_to_merge(left_data, left_size
					, right_data, right_size, &dst_data, &dst_size, dst_wh.audio_format) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 1, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size;
			}
		}
		else {
			short left_data[128] = { 0 };
			short right_data[128] = { 0 };
			short *dst_data = nullptr;
			unsigned int dst_size = 0;
			while (true) {
				unsigned int left_size = fread(left_data, 2, 128, left_file);
				unsigned int right_size = fread(right_data, 2, 128, right_file);

				if (left_size * 2 * 2 + data_length >= left_wh.data_length * 2) {
					left_size = left_wh.data_length / 2 - data_length / 4;
				}
				if (right_size * 2 * 2 + data_length >= right_wh.data_length * 2) {
					right_size = right_wh.data_length / 2 - data_length / 4;
				}
				if (data_length >= left_wh.data_length * 2) {
					left_size = 0;
				}
				if (data_length >= right_wh.data_length * 2) {
					right_size = 0;
				}
				if (left_size == 0 && right_size == 0) {
					break;
				}

				if (pcm_stereo_to_merge(left_data, left_size
					, right_data, right_size, &dst_data, &dst_size) != ERROR_SUCCESS) {
					break;
				}
				if (fwrite(dst_data, 2, dst_size, dst_file) != dst_size) {
					delete[] dst_data;
					break;
				}
				delete[] dst_data;
				data_length += dst_size * 2;
			}
		}
		fclose(left_file);
		fclose(right_file);
		fclose(dst_file);

		dst_wh.data_length = data_length;
		dst_wh.riff_length = data_length + dst_wh.length() - 8;
		return write_wav_header(dst_filename, &dst_wh, false);
	}

	int audio_convert::pcm8_to_pcm16(
		const char* const src_data, const unsigned int src_size
		, short** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = src_size;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples;
		*dst_data = new short[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[i] = (short)(src_data[i] - 128) << 8;
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_pcm8_to_pcm16(
		const char* const src_filename, const char* const dst_filename) {
		wav_header src_wh;
		int ret = read_wav_header(src_filename, &src_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (src_wh.audio_format != WAV_FORMAT_PCM
			|| src_wh.bits_per_sample != 8) {
			return ERROR_NOT_SUPPORTED;
		}

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(src_file, src_wh.length(), 0);
		if (ret != 0) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		wav_header dst_wh;
		dst_wh.init_pcm16();
		if (src_wh.channels == 2) {
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 32000;
			dst_wh.bytes_per_sample = 4;
		}

		ret = write_wav_header(dst_filename, &dst_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		FILE *dst_file = fopen(dst_filename, "ab");
		if (dst_file == nullptr) {
			fclose(src_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		char src_data[128] = { 0 };
		short *dst_data = nullptr;
		unsigned int dst_size = 0;
		while (true) {
			unsigned int size = fread(src_data, 1, 128, src_file);
			if (size * 2 + data_length >= src_wh.data_length * 2) {
				size = src_wh.data_length - data_length / 2;
			}
			if (size == 0) {
				break;
			}

			if (pcm8_to_pcm16(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
				break;
			}
			if (fwrite(dst_data, 2, dst_size, dst_file) != dst_size) {
				delete[] dst_data;
				break;
			}
			delete[] dst_data;
			data_length += dst_size * 2;
		}
		fclose(src_file);
		fclose(dst_file);

		dst_wh.data_length = data_length;
		dst_wh.riff_length = data_length + dst_wh.length() - 8;
		return write_wav_header(dst_filename, &dst_wh, false);
	}

	int audio_convert::pcm16_to_pcm8(
		const short* const src_data, const unsigned int src_size
		, char** const dst_data, unsigned int* const dst_size) {
		unsigned int samples = src_size;
		if (src_data == nullptr || samples == 0 || dst_data == nullptr || dst_size == nullptr) {
			return ERROR_INVALID_DATA;
		}

		*dst_size = samples;
		*dst_data = new char[*dst_size];
		for (unsigned int i = 0; i < samples; ++i) {
			(*dst_data)[i] = (src_data[i] >> 8) + 128;
		}
		return ERROR_SUCCESS;
	}

	int audio_convert::wav_pcm16_to_pcm8(
		const char* const src_filename, const char* const dst_filename) {
		wav_header src_wh;
		int ret = read_wav_header(src_filename, &src_wh);
		if (ret != ERROR_SUCCESS) {
			return ret;
		}

		if (src_wh.audio_format != WAV_FORMAT_PCM
			|| src_wh.bits_per_sample != 16) {
			return ERROR_NOT_SUPPORTED;
		}

		FILE *src_file = fopen(src_filename, "rb");
		if (src_file == nullptr) {
			return ERROR_FILE_NOT_FOUND;
		}

		ret = fseek(src_file, src_wh.length(), 0);
		if (ret != 0) {
			fclose(src_file);
			return ERROR_INVALID_DATA;
		}

		wav_header dst_wh;
		dst_wh.init_pcm8();
		if (src_wh.channels == 2) {
			dst_wh.channels = 2;
			dst_wh.bytes_per_second = 16000;
			dst_wh.bytes_per_sample = 2;
		}

		ret = write_wav_header(dst_filename, &dst_wh, true);
		if (ret != ERROR_SUCCESS) {
			fclose(src_file);
			return ret;
		}

		FILE *dst_file = fopen(dst_filename, "ab");
		if (dst_file == nullptr) {
			fclose(src_file);
			return ERROR_FILE_NOT_FOUND;
		}

		unsigned int data_length = 0;
		short src_data[128] = { 0 };
		char *dst_data = nullptr;
		unsigned int dst_size = 0;
		while (true) {
			unsigned int size = fread(src_data, 2, 128, src_file);
			if (size + data_length >= src_wh.data_length / 2) {
				size = src_wh.data_length / 2 - data_length;
			}
			if (size == 0) {
				break;
			}

			if (pcm16_to_pcm8(src_data, size, &dst_data, &dst_size) != ERROR_SUCCESS) {
				break;
			}
			if (fwrite(dst_data, 1, dst_size, dst_file) != dst_size) {
				delete[] dst_data;
				break;
			}
			delete[] dst_data;
			data_length += dst_size;
		}
		fclose(src_file);
		fclose(dst_file);

		dst_wh.data_length = data_length;
		dst_wh.riff_length = data_length + dst_wh.length() - 8;
		return write_wav_header(dst_filename, &dst_wh, false);
	}
	
}