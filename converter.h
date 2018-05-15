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

#ifndef OKULAR_GENERATOR_RFC_CONVERTER_H
#define OKULAR_GENERATOR_RFC_CONVERTER_H

#include "config.h"

#include <core/textdocumentgenerator.h>

#include <QFile>

namespace Rfc {

class Converter : public Okular::TextDocumentConverter
{
public:
    Converter();
    ~Converter();

private:
    QString &toHtml(QFile &file, QString &output);

private:
    void escapeCharacters(QString &line);
    bool parsePage(QTextStream &stream, QString &content, bool insertHeader = true);
    void parseHeader(QTextStream &stream, QString &output);
    void parseTitle(QTextStream &stream, QString &output);

public:
    virtual QTextDocument *convert(const QString &fileName);
};

} // namespace Rfc

#endif //OKULAR_GENERATOR_RFC_CONVERTER_H
