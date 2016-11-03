/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2016 QuantRisk

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

#ifndef qla_fx_hpp
#define qla_fx_hpp

#include <qlo/baseinstruments.hpp>
#include <qlo/leg.hpp>
#include <ql/qle/instruments/all.hpp>
#include <ql/exchangerate.hpp>
#include <ql/currency.hpp>
#include <ql/quote.hpp>


namespace QuantLib{
	class Date;
	class FxForward;
	class ExchangeRate;
	class Currency;
	class Money;
	class Quote;
	class leg;
}

namespace QuantLibAddin{
	/*
	FxForward(const Real& nominal1, const Currency& currency1, const Real& nominal2, 
	const Currency& currency2,const Date& maturityDate, const bool& payCurrency1)
	*/
	class FxForward : public Instrument{
	public:
		FxForward(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Real& nominal1, const QuantLib::Currency& currency1, 
			const QuantLib::Real& nominal2, const QuantLib::Currency& currency2,
			const QuantLib::Date& maturityDate, const bool& payCurrency1,
			bool permanent);
	};

	class FxForward2 : public Instrument{
	public:
		FxForward2(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Money& nominal1, const QuantLib::ExchangeRate& forwardRate, 
			const QuantLib::Date& forwardDate, bool sellingNominal,bool permanent);
	};

	class FxForward3 : public Instrument{
	public:
		FxForward3(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Money& nominal1, const QuantLib::Handle<QuantLib::Quote>& fxForwardQuote, 
			const QuantLib::Currency& currency2,
			const QuantLib::Date& maturityDate, bool sellingNominal,
			bool permanent);
	};

	class CrossCcySwap : public Instrument{
	public:
		CrossCcySwap(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Leg& firstLeg, const QuantLib::Currency& firstLegCcy, 
			const QuantLib::Leg& secondLeg, const QuantLib::Currency& secondLegCcy,
		    bool permanent);

	};


}

#endif