#pragma once

/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "DVDAudioCodec.h"
#include "DllLiba52.h"
#include "DllLibDts.h"

class CDVDAudioCodecPassthrough : public CDVDAudioCodec
{
public:
  CDVDAudioCodecPassthrough();
  virtual ~CDVDAudioCodecPassthrough();

  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose();
  virtual int Decode(BYTE* pData, int iSize);
  virtual int GetData(BYTE** dst);
  virtual void Reset();
  virtual int GetChannels();
  virtual int GetSampleRate();
  virtual int GetBitsPerSample();
  virtual unsigned char GetFlags();
  virtual const char* GetName()  { return "passthrough"; }
  
private:
  enum frametype
  {
    AC3 = 0,
    EAC3,
    DTS,
    TrueHD,
    DTS_HD
  };
  int ParseFrame(BYTE* data, int size, BYTE** frame, int* framesize, frametype* ft);
  int ParseTrueHDFrame(BYTE* buffer, int* sampleRate, int* bitRate);
  int ParseDTSHDFrame(BYTE* buffer, int* sampleRate, int* bitRate, int* samplesPerFrame );
  int PaddAC3Data( BYTE* pData, int iDataSize, BYTE* pOut);
  int PaddTrueHDData( BYTE* pData, int iDataSize, BYTE* pOut);
  int PaddDTSData( BYTE* pData, int iDataSize, BYTE* pOut);
  int PaddDTSHDData( BYTE* pData, int iDataSize, bool bIsDTSHDFrame, BYTE* pOut);
  
  BYTE m_OutputBuffer[131072];
  int  m_OutputSize;

  BYTE m_InputBuffer[4096];
  int  m_InputSize;

  int m_iFrameSize;

  int m_iSamplesPerFrame;
  int m_iSampleRate;
  int m_iChannels;

  int     m_Codec;
  bool    m_Synced;

  int m_iSourceFlags;
  int m_iSourceSampleRate;
  int m_iSourceBitrate;

  DllLibDts m_dllDTS;
  DllLiba52 m_dllA52;
  
  dts_state_t* m_pStateDTS;
  a52_state_t* m_pStateA52;

  // State tracking for trueHD streams
  int m_iByteCounter;
  unsigned int m_uiLastFrameTime;
  int m_iLastSampleRateBit;
  int m_iLastFrameSize;

  bool m_bIsDTSHD;
  bool m_bBitstreamDTSHD;

  bool m_bFirstDTSFrame;
  BYTE m_DTSPrevFrame[2048];
  int  m_DTSPrevFrameLen;
};