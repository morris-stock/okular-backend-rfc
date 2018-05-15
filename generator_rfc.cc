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

#include "generator_rfc.h"

#include "converter.h"

#include <kaboutdata.h>
#include <kconfigdialog.h>


RfcGenerator::RfcGenerator(QObject *parent, const QVariantList &args)
    : Okular::TextDocumentGenerator(new Rfc::Converter(), "okular_rfc_generator_settings", parent, args)
{
}

RfcGenerator::~RfcGenerator()
{
}

void RfcGenerator::addPages(KConfigDialog *dlg)
{
    Okular::TextDocumentSettingsWidget *widget = new Okular::TextDocumentSettingsWidget();

    dlg->addPage(widget, generalSettings(), i18n("RFC"), "text-plain", i18n("Plain RFC Backend Configuration"));
}


////////////////////////////////////////////////////////////////////////////////


namespace {

KAboutData createAboutData()
{
    KAboutData aboutData("okular_rfc",
                         "okular_rfc",
                         ki18n("Plain RFC Backend"),
                         "0.1",
                         ki18n("Plain RFC backend."),
                         KAboutData::License_GPL_V3,
                         ki18n("© 2018 Xiaofeng Wang"));

    aboutData.addAuthor(ki18n("Xiaofeng Wang"), KLocalizedString(), "wasphin@gmail.com");

    return aboutData;
}

} // namespace anonymous


OKULAR_EXPORT_PLUGIN(RfcGenerator, createAboutData())
