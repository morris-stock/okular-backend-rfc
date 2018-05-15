/*
 * RFC Backend for Okular
 * Copyright (C) 2018 by Xiaofeng Wang <wasphin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef OKULAR_GENERATOR_RFC_H
#define OKULAR_GENERATOR_RFC_H

#include <core/textdocumentgenerator.h>


class RfcGenerator : public Okular::TextDocumentGenerator
{
public:
    RfcGenerator(QObject *parent, const QVariantList &args);
    ~RfcGenerator();

public:
    void addPages(KConfigDialog *dlg);
};

#endif // OKULAR_GENERATOR_RFC_H
