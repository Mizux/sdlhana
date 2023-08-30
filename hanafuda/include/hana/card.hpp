//
// Copyright (c) 2005, 2006 Wei Mingzhi <whistler@openoffice.org>
// All Rights Reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA
//

#ifndef CARD_HPP
#define CARD_HPP

#include <cstdint>

enum class TYPE : std::uint8_t {
  NONE = 0,
  ANIMAL,
  RIBBON,
  RIBBON_RED,
  RIBBON_BLUE,
  LIGHT,
};

enum class EFFECT : std::uint8_t {
  NONE = 0,
  DARK = (1 << 0),
  BOX  = (1 << 1),
};

class CCard {
 public:
  using id_type = std::uint8_t;

  CCard(id_type value = 255);
  ~CCard();

  inline id_type GetID() const { return id_; }
  inline id_type GetMonth() const { return id_ / 4 + 1; }

  inline bool operator==(const CCard& c) const { return GetMonth() == c.GetMonth(); }
  inline bool operator!=(const CCard& c) const { return GetMonth() != c.GetMonth(); }

  enum TYPE  GetType() const;
  inline int GetOrder() const {
    switch (GetType()) {
      case TYPE::LIGHT:
        return 5;
      case TYPE::ANIMAL:
        return 4;
      case TYPE::RIBBON_BLUE:
        return 3;
      case TYPE::RIBBON_RED:
        return 2;
      case TYPE::RIBBON:
        return 1;
      case TYPE::NONE:
        return 0;
    }
  }
  inline bool IsRain() const { return (id_ == 40); }
  inline bool IsSakeCup() const { return (id_ == 32); }
  inline bool IsBoar() const { return (id_ == 24); }
  inline bool IsDeer() const { return (id_ == 36); }
  inline bool IsButterfly() const { return (id_ == 20); }
  inline bool IsMoon() const { return (id_ == 28); }
  inline bool IsFlower() const { return (id_ == 8); }
  inline bool IsBird() const { return (id_ == 4 || id_ == 12 || id_ == 29); }

  inline bool IsValid() const { return (id_ < 48); }
  inline void Destroy() { id_ = 255; }

  static void  NewRound();
  static CCard GetRandomCard();
  static void  PutBackToPile(const CCard& c);

  static unsigned char m_ucCardFlags[6];

  inline CCard Next() const {
    if (id_ >= 47)
      return CCard(0);
    return CCard(id_ + 1);
  }
  inline CCard Prev() const {
    if (id_ <= 1)
      return CCard(47);
    return CCard(id_ - 1);
  }

  unsigned int m_iRenderEffect;

 private:
  std::uint8_t id_;
};

#endif
