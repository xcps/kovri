/**
 * Copyright (c) 2013-2016, The Kovri I2P Router Project
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Parts of the project are originally copyright (c) 2013-2015 The PurpleI2P Project
 */

#ifndef SRC_CORE_TRANSPORT_TRANSPORTSESSION_H_
#define SRC_CORE_TRANSPORT_TRANSPORTSESSION_H_

#include <inttypes.h>

#include <iostream>
#include <memory>
#include <vector>

#include "I2NPProtocol.h"
#include "Identity.h"
#include "RouterInfo.h"

namespace i2p {
namespace transport {

struct DHKeysPair {  // transient keys for transport sessions
  uint8_t publicKey[256];
  uint8_t privateKey[256];
};

class SignedData {
 public:
  SignedData() {}
  SignedData(
      const SignedData &data) {
    m_Stream << data.m_Stream.rdbuf();
  }

  void Insert(
      const uint8_t* buf,
      size_t len) {
    m_Stream.write((char *)buf, len);
  }
  template<typename T>
  void Insert(
      T t) {
    m_Stream.write((char *)&t, sizeof(T));
  }

  bool Verify(
      const i2p::data::IdentityEx& ident,
      const uint8_t* signature) const {
    return ident.Verify(
        (const uint8_t *)m_Stream.str().c_str(),
        m_Stream.str().size(),
        signature);
  }

  void Sign(
      const i2p::data::PrivateKeys& keys,
      uint8_t* signature) const {
    keys.Sign(
        (const uint8_t *)m_Stream.str().c_str(),
        m_Stream.str().size(),
        signature);
  }

 private:
  std::stringstream m_Stream;
};

class TransportSession {
 public:
  TransportSession(
      std::shared_ptr<const i2p::data::RouterInfo> in_RemoteRouter)
      : m_RemoteRouter(in_RemoteRouter),
        m_DHKeysPair(nullptr),
        m_NumSentBytes(0),
        m_NumReceivedBytes(0),
        m_IsOutbound(in_RemoteRouter) {
    if (m_RemoteRouter)
      m_RemoteIdentity = m_RemoteRouter->GetRouterIdentity();
  }

  virtual ~TransportSession() {
    delete m_DHKeysPair;
  }

  virtual void Done() = 0;

  std::shared_ptr<const i2p::data::RouterInfo> GetRemoteRouter() {
    return m_RemoteRouter;
  }

  const i2p::data::IdentityEx& GetRemoteIdentity() {
    return m_RemoteIdentity;
  }

  size_t GetNumSentBytes() const {
    return m_NumSentBytes;
  }

  size_t GetNumReceivedBytes() const {
    return m_NumReceivedBytes;
  }

  bool IsOutbound() const {
    return m_IsOutbound;
  }

  virtual void SendI2NPMessages(
      const std::vector<std::shared_ptr<I2NPMessage> >& msgs) = 0;

 protected:
  std::shared_ptr<const i2p::data::RouterInfo> m_RemoteRouter;
  i2p::data::IdentityEx m_RemoteIdentity;
  DHKeysPair* m_DHKeysPair;  // X - for client and Y - for server
  size_t m_NumSentBytes,
         m_NumReceivedBytes;
  bool m_IsOutbound;
};

}  // namespace transport
}  // namespace i2p

#endif  // SRC_CORE_TRANSPORT_TRANSPORTSESSION_H_
