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

#include "converter.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextFrame>

namespace Rfc {

Converter::Converter()
{
}

Converter::~Converter()
{
}

void Converter::escapeCharacters(QString &line)
{
    line.replace(QChar('&'), QString("&amp;"));
    line.replace(QChar('<'), QString("&lt;"));
    line.replace(QChar('>'), QString("&gt;"));
    line.replace(QChar('\"'), QString("&quot;"));
}

bool Converter::parsePage(QTextStream &stream, QString &content, bool insertHeader)
{
    content.clear();

    QRegExp regExpFooter("\\[Page\\s\\d+\\]$");
    QRegExp regExpHeader("^RFC\\s\\d+\\s+.*$");

    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine();
        escapeCharacters(line);
        if (insertHeader) {
            line.prepend("<hr><font color=\"Grey\">");
            line.append("</font></hr>");
            insertHeader = false;
        } else if (regExpFooter.indexIn(line) != -1) {
            line.prepend("<font color=\"Grey\">");
            line.append("</font>");
        } else if (line.indexOf('\f') != -1) {
            return true;
        }
        content += line + "\n";
    }

    return false;
}

void Converter::parseHeader(QTextStream &stream, QString &output)
{
    QString authors;
    QString candidate;

    QString line;
    do {
        line = stream.readLine();
        escapeCharacters(line);

        if (line.isEmpty()) {
            output.append("\n");

            if (!candidate.isEmpty()) {
                emit addMetaData(Okular::DocumentInfo::CreationDate, candidate);
                break;
            }

            continue;
        }

        QStringList fields = line.split("  ", QString::SkipEmptyParts);
        if (!candidate.isEmpty()) {
            if (!authors.isEmpty())
                authors.append(", ");
            authors.append(candidate);
            candidate.clear();
        } else {
            if (fields.size() > 1) {
                Q_ASSERT(fields.size() == 2);
                candidate = fields.at(1);
            } else {
                candidate = fields.at(0);
            }
        }

        output += line + "\n";
    } while (!stream.atEnd());

    if (!authors.isEmpty())
        emit addMetaData(Okular::DocumentInfo::Author, authors);
}

void Converter::parseTitle(QTextStream &stream, QString &output)
{
    QString title;

    QRegExp regExpTitle("(\\s*)(\\w.*)$");

    QString line;
    do {
        line = stream.readLine();
        if (line.isEmpty()) {
            output += "\n";

            if (!title.isEmpty())
                break;

            continue;
        }

        if (regExpTitle.indexIn(line) != -1) {
            if (!title.isEmpty())
                title += " ";
            title += regExpTitle.cap(2);

            line.replace(regExpTitle, "\\1<b>\\2</b>");
        }

        output += line + "\n";
    } while (!stream.atEnd());

    if (!title.isEmpty())
        emit addMetaData(Okular::DocumentInfo::Title, title);
}

QTextDocument* Converter::convert(const QString &fileName)
{
    QFile plainFile(fileName);
    if (!plainFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        kWarning() << "Can't open file" << plainFile.fileName() << ", error:" << plainFile.errorString();
        return NULL;
    }

    QTextDocument *textDocument = new QTextDocument();
    /* todo: calculate page size based on size */
    textDocument->setPageSize(QSizeF(1200, 1600));

    /* todo: page layout */
    QTextFrameFormat frameFormat;
    frameFormat.setMargin(100);
    QTextFrame *rootFrame = textDocument->rootFrame();
    rootFrame->setFrameFormat(frameFormat);

    const QString preHtml = QString("<html><body><pre>");
    const QString postHtml = QString("</pre></body></html>");

    {
        QSharedPointer<QTextCursor> cursor(new QTextCursor(textDocument));
        QString htmlContent;
        htmlContent.reserve(72*60);

        QTextStream textStream(&plainFile);
        while (parsePage(textStream, htmlContent, !htmlContent.isEmpty())) {
            cursor->insertHtml(preHtml + htmlContent + postHtml);
            kWarning() << preHtml + htmlContent + postHtml;
            cursor->insertBlock();
        }
    }

    emit addMetaData(Okular::DocumentInfo::MimeType, "text/plain");

    return textDocument;
}

} // namespace Rfc
