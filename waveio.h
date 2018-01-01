/*
 * Copyright 2004 Riccardo Bernardini
 *
 * This file is part of WaveIO.
 *
 * WaveIO is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
 
#ifndef __WAVEIO_H__
#define __WAVEIO_H__
 
extern int   waveio_errno;     
extern char *waveio_errmsg[];  
#define WAVEIO_OK   0  
#define WAVEIO_EOF -1          
#define WAVEIO_OUT_OF_ROOM -2  
#define WAVEIO_INV         -3  
#define WAVEIO_NO_PCM      -4  
typedef short int16;
typedef int   int32;
 
typedef struct {
  /* Begin of FMT chunk */
  char fmt[4];            /* String "fmt ". */
  int32 chunk_length;     /* Length of FMT chunk >= 16 byte. */
  int16 format_type;      /* Format tag (1=PCM). */
  int16 channels;         
  int32 sampling_freq;    
  int32 byte_per_sec;     
  int16 byte_by_capture;  
  int16 bit_per_sample;   
} wav_fmt;

typedef struct {
  FILE *stream;   
  wav_fmt fmt_info; 
  int nsamples;     
  int  idx;
  char mode;   /* 'r' => open for reading, 'w' => writing */
} WAV_FILE;

typedef struct {
  int bit_per_sample;  
  int nsamples;        
  int nchannels;       
  int freq;            
  int16 *chan0;        
  int16 *chan1;        
} wav_samples;
 
 
 
WAV_FILE *open_input_wav(char *filename);
 
WAV_FILE *open_output_wav(char *filename,
                          int nchan,      
                          int nbits,      
                          int freq        
                          );

void close_wav_file(WAV_FILE *f);

int write_wav_samples(WAV_FILE *Output, void *buf, int how_many);
 
int read_wav_samples(WAV_FILE *Input, void *buf, int how_many);
 
wav_samples *slurp_wav_file(char *filename);
 
void destroy_wav_samples(wav_samples *w);
 
void waveio_perror(char *msg);
 
#endif

