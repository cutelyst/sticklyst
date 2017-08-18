/***************************************************************************
 *   Copyright (C) 2017 Daniel Nicoletti <dantti12@gmail.com>              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; see the file COPYING. If not, write to       *
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/
#include "root.h"

#include "htmlhighlighter.h"

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent),
    m_htmlHighlighter(new HtmlHighlighter)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    c->setStash(QStringLiteral("languages"), QVariant::fromValue(m_htmlHighlighter->definitions()));
}

void Root::item(Context *c, const QString &id)
{

}

void Root::create(Context *c)
{
    if (!c->request()->isPost()) {
        c->res()->redirect(c->uriFor(actionFor(QStringLiteral("index"))));
        return;
    }

    const ParamsMultiMap params = c->request()->bodyParams();
    const QString title = params.value(QStringLiteral("title"));
    const QString definition = params.value(QStringLiteral("language"));
    const QString expire = params.value(QStringLiteral("expire"));
    const QString priv = params.value(QStringLiteral("private"));

    QString data = params.value(QStringLiteral("data"));
    const QString dataHighlighted = m_htmlHighlighter->highlightString(definition, QStringLiteral("Default"), &data);

    QString id;

    c->res()->redirect(c->uriFor(actionFor(QStringLiteral("item")), QStringList{ id }));
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

