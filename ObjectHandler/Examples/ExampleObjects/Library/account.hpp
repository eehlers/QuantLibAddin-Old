
/*!
 Copyright (C) 2004, 2005, 2006, 2007 Eric Ehlers

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

#ifndef example_account_hpp
#define example_account_hpp

#include <string>
#include <sstream>

namespace AccountExample {

    class Account {
    public:

        enum Type { Savings, Current };

        Account(const int &number,
            const Type &type,
            const int &balance = 0)
            : number_(number), type_(type), balance_(balance) {}

        void setBalance(const int &balance) { balance_ = balance; }
        const int &balance() { return balance_; }
        std::string type() {
            std::ostringstream s;
            s << type_;
            return s.str();
        }

    private:
        int number_;
        Type type_;
        int balance_;
    };

}

#endif

