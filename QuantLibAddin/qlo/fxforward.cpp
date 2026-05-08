/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/fxforward.hpp>

namespace QuantLibAddin {

    FxForward::FxForward(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Real sourceNominal,
            const QuantLib::Currency& sourceCurrency,
            QuantLib::Real targetNominal,
            const QuantLib::Currency& targetCurrency,
            const QuantLib::Date& maturityDate,
            bool paySourceCurrency,
            QuantLib::Natural settlementDays,
            const QuantLib::Calendar& paymentCalendar,
            bool permanent)
        : Instrument(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(
            new QuantLib::FxForward(
                sourceNominal,
                sourceCurrency,
                targetNominal,
                targetCurrency,
                maturityDate,
                paySourceCurrency,
                settlementDays,
                paymentCalendar));
    }

    DiscountingFxForwardEngine::DiscountingFxForwardEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& sourceCcyDiscountCurve,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& targetCcyDiscountCurve,
            const QuantLib::Handle<QuantLib::Quote>& spotFx,
            bool permanent)
        : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::DiscountingFxForwardEngine(
                sourceCcyDiscountCurve,
                targetCcyDiscountCurve,
                spotFx));
    }

}
