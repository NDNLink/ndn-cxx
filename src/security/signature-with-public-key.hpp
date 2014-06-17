/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2014 Regents of the University of California.
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

#ifndef NDN_SECURITY_SIGNATURE_WITH_PUBLIC_KEY_HPP
#define NDN_SECURITY_SIGNATURE_WITH_PUBLIC_KEY_HPP

#include "../data.hpp"
#include "../encoding/tlv.hpp"

namespace ndn {

/**
 * Base class of public key signature.
 */
class SignatureWithPublicKey : public Signature
{
public:
  class Error : public Signature::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : Signature::Error(what)
    {
    }
  };

  explicit
  SignatureWithPublicKey(const Tlv::SignatureTypeValue& signatureType)
  {
    m_info = Block(Tlv::SignatureInfo);

    m_type = signatureType;
    m_info.push_back(nonNegativeIntegerBlock(Tlv::SignatureType, signatureType));
    m_info.push_back(m_keyLocator.wireEncode());
  }

  explicit
  SignatureWithPublicKey(const Signature& signature)
    : Signature(signature)
  {
    m_info.parse();
    Block::element_const_iterator i = m_info.find(Tlv::KeyLocator);
    if (i != m_info.elements_end())
      {
        m_keyLocator.wireDecode(*i);
      }
  }

  const KeyLocator&
  getKeyLocator() const
  {
    return m_keyLocator;
  }

  void
  setKeyLocator(const KeyLocator& keyLocator)
  {
    m_keyLocator = keyLocator;

    m_info.remove(ndn::Tlv::KeyLocator);
    m_info.push_back(m_keyLocator.wireEncode());
  }

private:
  KeyLocator m_keyLocator;
};

} // namespace ndn

#endif //NDN_SECURITY_SIGNATURE_WITH_PUBLIC_KEY_HPP
