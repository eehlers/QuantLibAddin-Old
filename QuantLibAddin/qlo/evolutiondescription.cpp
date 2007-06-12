
/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti

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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif
#include <qlo/evolutiondescription.hpp>

namespace QuantLibAddin {
    
    EvolutionDescription::EvolutionDescription(
            const std::vector<QuantLib::Time>& rateTimes,
            const std::vector<QuantLib::Time>& evolutionTimes)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(rateTimes, evolutionTimes));
    }

    EvolutionDescription::EvolutionDescription(
            const QuantLib::EvolutionDescription& ev)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(ev));
    }

    EvolutionDescription::EvolutionDescription(
            const QuantLib::MarketModelMultiProduct& product)
    {
        const QuantLib::EvolutionDescription& ev = product.evolution();
        libraryObject_ =
           boost::shared_ptr< QuantLib::EvolutionDescription>(new QuantLib::EvolutionDescription(ev));
    }


}