/*
 * This file is a part of Moorie
 *
 * Copyright (C) 2007-2010 Moorie Team - http://moorie.pl/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "GoogleApps.h"
#include "mailboxfactory.h"

#include <sstream>
namespace {
    mailbox* Create(const std::string& name,
                     const std::string& username,
                     const std::string& password)
    {
        return new GoogleAppsMailbox(name, username, password);
    }
}

const std::string c_names[] = {
    "gala.net",
    "gazeta.pl",
    "mailbox.hu",
    "vivapolska.tv",
    "gde.ru",
    "klikni.cz",
    "livedoor.com",
    "oneindia.in",
    "bigmir.net",
    "sify.com",
    std::string()
};
const bool registered = MailboxFactory::Instance().Register(c_names, Create);

GoogleAppsMailbox::GoogleAppsMailbox(const std::string &name, const std::string &usr, const std::string
                                     &passwd)
                                         : mailbox(),
                                         totalEmails( 0 )
{
}

int GoogleAppsMailbox::loginRequest()
{

}

void GoogleAppsMailbox::logoutRequest()
{
    //	setState(Mailbox::Disconnected); //TODO
}

void GoogleAppsMailbox::getHeadersRequest()
{
}

int GoogleAppsMailbox::downloadRequest(int seg)
{
}

int GoogleAppsMailbox::uploadRequest(std::string filename, std::vector<std::string> to, int seg) {
   // std::string segCRC = getSegCRC(filename);
}

GoogleAppsMailbox::~GoogleAppsMailbox()
{
}

void GoogleAppsMailbox::parseResponse()
{
    //	const Mailbox::State state = getState();
}

