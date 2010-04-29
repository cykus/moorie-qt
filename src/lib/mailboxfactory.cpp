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

#include "mailboxfactory.h"

MailboxFactory* MailboxFactory::instance_ = 0;

MailboxFactory& MailboxFactory::Instance() {
    if (!instance_)
        instance_ = new MailboxFactory;

    return *instance_;
}

bool
        MailboxFactory::Register(const QString& name, MailboxCreator creator) {
    return creators_.insert(name, creator).value();
}

bool
        MailboxFactory::Register(const QString names[], MailboxCreator creator) {
    bool result;
    for (unsigned int i = 0; !names[i].isEmpty() ; ++i) {
        result = creators_.insert(names[i], creator).value();
        if (!result)
            break;
    }

    return result;
}

bool MailboxFactory::Registered(const QString& name) {
    return (creators_.find(name) != creators_.end());
}

bool MailboxFactory::Unregister(const QString& name) {
    return (creators_.remove(name) == 1);
}

Mailbox* MailboxFactory::Create(const QString& name,
                                const QString& username,
                                const QString& password)
{
    CreatorMap::const_iterator it = creators_.find(name);
    if (it != creators_.end()) {
        try {
            return (it.value())(name, username, password);
        }
        catch (...) {
            // Hopefully only std::bad_alloc can be thrown here.
            return 0;
        }
    }

    return 0;
}

MailboxFactory::MailboxFactory() {}
