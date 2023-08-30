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

#include "hana/card.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_set>

unsigned char CCard::m_ucCardFlags[6];

CCard::CCard(id_type value) : m_iRenderEffect(0), id_(value) {}

CCard::~CCard() {}

enum TYPE CCard::GetType() const {
  std::unordered_set<int> lights = {0, 8, 28, 40, 44, 255};
  if (lights.contains(id_))
    return TYPE::LIGHT;

  std::unordered_set<int> animals = {4, 12, 16, 20, 24, 29, 32, 36, 41, 255};
  if (animals.contains(id_))
    return TYPE::ANIMAL;

  std::unordered_set<int> ribbons = {13, 17, 25, 42, 255};
  if (ribbons.contains(id_))
    return TYPE::RIBBON;

  std::unordered_set<int> ribbons_red = {1, 5, 9, 255};
  if (ribbons_red.contains(id_))
    return TYPE::RIBBON_RED;

  std::unordered_set<int> ribbons_blue = {21, 33, 37, 255};
  if (ribbons_blue.contains(id_))
    return TYPE::RIBBON_BLUE;

  return TYPE::NONE;
}

void CCard::NewRound() {
  ::memset(m_ucCardFlags, 0, sizeof(m_ucCardFlags));
}

CCard CCard::GetRandomCard() {
  unsigned char a[48], i;
  char          count = 0;

  for (i = 0; i < 48; i++) {
    if (!(m_ucCardFlags[i / 8] & (1 << (i & 7)))) {
      a[count++] = i;
    }
  }

  count--;
  if (count < 0) {
    std::cerr << "CCard::GetRandomCard(): No cards left!";
    exit(1);
  }

  i = rand() % count;
  m_ucCardFlags[a[i] / 8] |= (1 << (a[i] & 7));

  return CCard(a[i]);
}

void CCard::PutBackToPile(const CCard& c) {
  assert(c.IsValid());
  unsigned char value = c.GetID();
  m_ucCardFlags[value / 8] &= ~(1 << (value & 7));
}
