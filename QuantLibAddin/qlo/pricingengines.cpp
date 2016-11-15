/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007, 2012 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2015 Paolo Mazzocchi
 Copyright (C) 2016 Stefano Fondi

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

#include <qlo/pricingengines.hpp>
#include <qlo/swaption.hpp>
#include <qlo/enumerations/factories/pricingenginesfactory.hpp>

#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/blackcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/bacheliercapfloorengine.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/pricingengines/swaption/treeswaptionengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
#include <ql/qle/pricingengines/discountingfxforwardengine.hpp>
#include <ql/qle/pricingengines/discountingcurrencyswapengine.hpp>
#include <ql/qle/pricingengines/crossccyswapengine.hpp>

namespace QuantLibAddin {

    // PricingEngines - without timesteps
    PricingEngine::PricingEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& engineID,
            const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
            bool permanent) : ObjectHandler::LibraryObject<QuantLib::PricingEngine>(properties, permanent)
    {
        libraryObject_ = ObjectHandler::createPricingEngine(engineID, process);
    }

    // PricingEngines - with timesteps
    PricingEngine::PricingEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& engineID,
            const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
            const long& timeSteps,
            bool permanent) : ObjectHandler::LibraryObject<QuantLib::PricingEngine>(properties, permanent)
    {
        libraryObject_ = ObjectHandler::createPricingEngine(engineID, process, timeSteps);
    }

    DiscountingSwapEngine::DiscountingSwapEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        bool includeSettlementDateFlows,
        const QuantLib::Date& settlementDate,
        const QuantLib::Date& npvDate,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::DiscountingSwapEngine(hYTS, includeSettlementDateFlows,
                                            settlementDate, npvDate));
    }

    BlackSwaptionEngine::BlackSwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        const QuantLib::Handle<QuantLib::Quote>& vol,
        const QuantLib::Real displacement,
        const QuantLib::DayCounter& dayCounter,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::BlackSwaptionEngine(hYTS, vol, dayCounter, displacement));
    }

    BlackSwaptionEngine::BlackSwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& vol,
        const QuantLib::Real displacement,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::BlackSwaptionEngine(hYTS, vol, displacement));
    }

    BlackCapFloorEngine::BlackCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        const QuantLib::Handle<QuantLib::Quote>& vol,
        const QuantLib::Real displacement,
        const QuantLib::DayCounter& dayCounter,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::BlackCapFloorEngine(hYTS, vol, dayCounter, displacement));
    }

    BlackCapFloorEngine::BlackCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        const QuantLib::Handle<QuantLib::OptionletVolatilityStructure>& vol,
        const QuantLib::Real displacement,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::BlackCapFloorEngine(hYTS, vol, displacement));
    }

    BachelierCapFloorEngine::BachelierCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
        const QuantLib::Handle<QuantLib::Quote>& vol,
        const QuantLib::DayCounter& dayCounter,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::BachelierCapFloorEngine(discountCurve, vol, dayCounter));
    }

    BachelierCapFloorEngine::BachelierCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
        const QuantLib::Handle<QuantLib::OptionletVolatilityStructure>& vol,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::BachelierCapFloorEngine(discountCurve, vol));
    }

    AnalyticCapFloorEngine::AnalyticCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr < QuantLib::AffineModel >& model,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::AnalyticCapFloorEngine(model));
    }

    BlackCalculator::BlackCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        QuantLib::Option::Type optionType,
        QuantLib::Real strike,
        QuantLib::Real forward,
        QuantLib::Real stdDev,
        QuantLib::DiscountFactor discount,
        bool permanent)
        : ObjectHandler::LibraryObject<QuantLib::BlackCalculator>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::BlackCalculator>(new
            QuantLib::BlackCalculator(optionType, strike,
                                      forward, stdDev, discount));
    }

    BlackCalculator::BlackCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::StrikedTypePayoff>& payoff,
        QuantLib::Real forward,
        QuantLib::Real stdDev,
        QuantLib::DiscountFactor discount,
        bool permanent)
        : ObjectHandler::LibraryObject<QuantLib::BlackCalculator>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::BlackCalculator>(new
            QuantLib::BlackCalculator(payoff,
                                      forward, stdDev, discount));
    }

    BlackScholesCalculator::BlackScholesCalculator(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Option::Type optionType,
            QuantLib::Real strike,
            QuantLib::Real spot,
            QuantLib::DiscountFactor growth,
            QuantLib::Real stdDev,
            QuantLib::DiscountFactor discount,
            bool permanent) : BlackCalculator(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::BlackCalculator>(new
            QuantLib::BlackScholesCalculator(optionType, strike,
                                             spot, growth, stdDev, discount));
    }

    BlackScholesCalculator::BlackScholesCalculator(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::StrikedTypePayoff>& payoff,
            QuantLib::Real spot,
            QuantLib::DiscountFactor growth,
            QuantLib::Real stdDev,
            QuantLib::DiscountFactor discount,
            bool permanent) : BlackCalculator(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::BlackCalculator>(new
            QuantLib::BlackScholesCalculator(payoff,
                                             spot, growth, stdDev, discount));
    }

    BondEngine::BondEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::DiscountingBondEngine(discountCurve));
    }

    JamshidianSwaptionEngine::JamshidianSwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::OneFactorAffineModel>& model,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::JamshidianSwaptionEngine(model, termStructure));
    }

    TreeSwaptionEngine::TreeSwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::OneFactorAffineModel>& model,
        QuantLib::Size timeSteps,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::TreeSwaptionEngine(model, timeSteps, termStructure));
    }

    G2SwaptionEngine::G2SwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::G2>& model,
        QuantLib::Real range,
        QuantLib::Size intervals,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::G2SwaptionEngine(model, range, intervals));
    }

		DiscountingFxForwardEngine::DiscountingFxForwardEngine(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Currency& ccy1,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& currency1Discountcurve,
		const QuantLib::Currency& ccy2,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& currency2Discountcurve,
		QuantLib::Handle<QuantLib::Quote>& spotFX,
		bool includeSettlementDateFlows,
		const QuantLib::Date& settlementDate,
		const QuantLib::Date& npvDate,
		bool permanent):PricingEngine(properties,permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::DiscountingFxForwardEngine(ccy1,currency1Discountcurve,
			                                     ccy2,currency2Discountcurve,spotFX,
												 includeSettlementDateFlows,
						                                     settlementDate,npvDate));

	}

	CrossCcySwapEngine::CrossCcySwapEngine(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Currency& ccy1,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& currency1Discountcurve,
		const QuantLib::Currency& ccy2,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& currency2Discountcurve,
		QuantLib::Handle<QuantLib::Quote>& spotFX,
		bool includeSettlementDateFlows,
		const QuantLib::Date& settlementDate,
		const QuantLib::Date& npvDate,
		bool permanent):PricingEngine(properties,permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::CrossCcySwapEngine(ccy1,currency1Discountcurve,
			ccy2,currency2Discountcurve,spotFX,
			includeSettlementDateFlows,
			settlementDate,npvDate));

	}

	DiscountingCurrencySwapEngine::DiscountingCurrencySwapEngine(			
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const std::vector<QuantLib::Handle<QuantLib::YieldTermStructure> >& discountCurves,
		const std::vector<QuantLib::Handle<QuantLib::Quote> >& fxQuotes, 
		const std::vector<QuantLib::Currency>& currencies,
		const QuantLib::Currency& npvCurrency,
		bool includeSettlementDateFlows,
		const QuantLib::Date& settlementDate,
		const QuantLib::Date& npvDate,
		bool permanent) : PricingEngine(properties,permanent){
			libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
				QuantLib::DiscountingCurrencySwapEngine(discountCurves,fxQuotes,currencies,
				                                        npvCurrency,includeSettlementDateFlows,
				                                                  settlementDate,npvDate));

	}

}