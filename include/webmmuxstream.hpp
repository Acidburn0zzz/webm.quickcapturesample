// Copyright (c) 2010 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.

#ifndef WEBMMUXSTREAM_HPP
#define WEBMMUXSTREAM_HPP

namespace webmmux
{
class Context;
class MediaSampleInterface;

class Stream
{
  Stream(Stream&);
  Stream& operator=(const Stream&);

public:
  virtual ~Stream();
  virtual void Final();  // grant last wishes

  virtual void WriteTrackEntry(int tn);

  virtual int Receive(MediaSampleInterface* pSample) = 0;
  virtual int EndOfStream() = 0;
  virtual void Flush() = 0;
  virtual bool Wait() const = 0;

  void SetTrackNumber(int tn);
  int GetTrackNumber() const;

  class Frame
  {
    Frame(const Frame&);
    Frame& operator=(const Frame&);

  protected:
    Frame();
    virtual ~Frame();

  public:
    virtual bool IsKey() const = 0;
    virtual void Write(const Stream& stream,
                       unsigned long cluster_timecode) const;
    virtual unsigned long GetTimecode() const = 0;
    virtual const unsigned char* GetData() const = 0;
    virtual unsigned long GetSize() const = 0;
    virtual void Release();
  };

  Context& m_context;

protected:
  explicit Stream(Context&);

  typedef long long TrackUID_t;
  static TrackUID_t CreateTrackUID();

  int m_trackNumber;

  virtual void WriteTrackNumber(int tn);
  virtual void WriteTrackUID();
  virtual void WriteTrackType() = 0;
  virtual void WriteTrackName();
  virtual void WriteTrackCodecID() = 0;
  virtual void WriteTrackCodecPrivate();
  virtual void WriteTrackCodecName() = 0;
  virtual void WriteTrackSettings();
};

}  // namespace webmmux

#endif  // WEBMMUXSTREAM_HPP
