/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef qla_fxforward_hpp
#define qla_fxforward_hpp

#include <qlo/baseinstruments.hpp>
#include <qlo/pricingengines.hpp>
#include <ql/instruments/fxforward.hpp>
#include <ql/pricingengines/forward/discountingfxforwardengine.hpp>
#include <ql/currency.hpp>
#include <ql/time/calendar.hpp>

namespace QuantLibAddin {

    class FxForward : public Instrument {
      public:
        FxForward(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Real sourceNominal,
            const QuantLib::Currency& sourceCurrency,
            QuantLib::Real targetNominal,
            const QuantLib::Currency& targetCurrency,
            const QuantLib::Date& maturityDate,
            bool paySourceCurrency,
            QuantLib::Natural settlementDays,
            const QuantLib::Calendar& paymentCalendar,
            bool permanent);
    };

    class DiscountingFxForwardEngine : public PricingEngine {
      public:
        DiscountingFxForwardEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& sourceCcyDiscountCurve,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& targetCcyDiscountCurve,
            const QuantLib::Handle<QuantLib::Quote>& spotFx,
            bool permanent);
    };

}

#endif
