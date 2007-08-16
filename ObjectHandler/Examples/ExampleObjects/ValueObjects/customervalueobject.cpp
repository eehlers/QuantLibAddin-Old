
/*!
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ExampleObjects/ValueObjects/customervalueobject.hpp>
#include <oh/exception.hpp>
#include <iostream>

namespace AccountExample {

    const char* CustomerValueObject::mPropertyNames[] = {
        "ObjectID",
        "ClassName",
        "Permanent",
        "Name",
        "Age"};

    std::vector<std::string> CustomerValueObject::getPropertyNames() const {
        return std::vector<std::string>(mPropertyNames,
            mPropertyNames + sizeof(mPropertyNames)/sizeof(const char*));
    }

    boost::any CustomerValueObject::getProperty(const std::string& name) const {
        if(name == "ObjectID") return objectID_;
        else if(name == "ClassName") return className_;
        else if(name == "Permanent") return permanent_;
        else if(name == "Name") return name_;
        else if(name == "Age") return age_;
        else 
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void CustomerValueObject::setProperty(const std::string& name, const boost::any& value) {
        if(name == "ObjectID") objectID_ = boost::any_cast<std::string>(value);
        else if(name == "ClassName") className_ = boost::any_cast<std::string>(value);
        else if(name == "Permanent") name_ = boost::any_cast<bool>(value);
        else if(name == "Name") name_ = boost::any_cast<std::string>(value);
        else if(name == "Age") age_ = boost::any_cast<long>(value);
        else 
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

}

