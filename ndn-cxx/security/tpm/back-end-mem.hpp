/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013-2019 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#ifndef NDN_SECURITY_TPM_BACK_END_MEM_HPP
#define NDN_SECURITY_TPM_BACK_END_MEM_HPP

#include "ndn-cxx/security/tpm/back-end.hpp"

namespace ndn {
namespace security {
namespace tpm {

/**
 * @brief The back-end implementation of an in-memory TPM.
 */
class BackEndMem final : public BackEnd
{
public:
  /**
   * @brief Create memory-based TPM backend.
   *
   * @param location Not used (required by the TPM registration interface).
   */
  explicit
  BackEndMem(const std::string& location = "");

  ~BackEndMem() final;

  static const std::string&
  getScheme();

private: // inherited from tpm::BackEnd
  bool
  doHasKey(const Name& keyName) const final;

  unique_ptr<KeyHandle>
  doGetKeyHandle(const Name& keyName) const final;

  unique_ptr<KeyHandle>
  doCreateKey(const Name& identityName, const KeyParams& params) final;

  void
  doDeleteKey(const Name& keyName) final;

  ConstBufferPtr
  doExportKey(const Name& keyName, const char* pw, size_t pwLen) final;

  void
  doImportKey(const Name& keyName, const uint8_t* buf, size_t size, const char* pw, size_t pwLen) final;

  void
  doImportKey(const Name& keyName, shared_ptr<transform::PrivateKey> key) final;

private:
  class Impl;
  const unique_ptr<Impl> m_impl;
};

} // namespace tpm
} // namespace security
} // namespace ndn

#endif // NDN_SECURITY_TPM_BACK_END_MEM_HPP
