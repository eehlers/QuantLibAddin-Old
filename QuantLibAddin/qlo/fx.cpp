/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2016 QuantLib

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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/fx.hpp>
#include <qlo/leg.hpp>

namespace QuantLibAddin{
	FxForward::FxForward(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Real& nominal1, const QuantLib::Currency& currency1, 
		const QuantLib::Real& nominal2, const QuantLib::Currency& currency2,
		const QuantLib::Date& maturityDate, const bool& payCurrency1,
		bool permanent) : Instrument(properties,permanent){
			libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(new
				QuantLib::FxForward(nominal1,currency1,nominal2,
				                    currency2,maturityDate,payCurrency1));

			}

	FxForward2::FxForward2(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Money& nominal1, const QuantLib::ExchangeRate& forwardRate, 
		const QuantLib::Date& forwardDate, bool sellingNominal,bool permanent): Instrument(properties,permanent){
			libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(new
				QuantLib::FxForward(nominal1,forwardRate,forwardDate,sellingNominal));
	}

	FxForward3::FxForward3(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Money& nominal1, const QuantLib::Handle<QuantLib::Quote>& fxForwardQuote, 
		const QuantLib::Currency& currency2,
		const QuantLib::Date& maturityDate, bool sellingNominal,
		bool permanent) : Instrument(properties,permanent){
			libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(new
				QuantLib::FxForward(nominal1,fxForwardQuote,currency2,maturityDate,sellingNominal));
	}

	CrossCcySwap::CrossCcySwap(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Leg& firstLeg, const QuantLib::Currency& firstLegCcy, 
		const QuantLib::Leg& secondLeg, const QuantLib::Currency& secondLegCcy,
		bool permanent) : Instrument(properties,permanent){
			libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(new
				QuantLib::CrossCcySwap(firstLeg,firstLegCcy,secondLeg,secondLegCcy));
	}
}