#include <contract/contract.hpp>

#include "contract_error.hpp"

#include <boost/test/unit_test.hpp>

namespace
{

class account
{
public:
    account(int bal, bool skip_pre = false)
        : balance_(-1)
    {
        contract(ctor)
        {
            precondition(bal > 0 || skip_pre);
            postcondition(balance_ > 0);
        };

        balance_ = bal;  // after balance_ is assigned the postcondition succeeds
    }

private:
    int balance_;
};

}

BOOST_AUTO_TEST_CASE(ctor_contract)
{
    test::contract_handler_frame cframe;

    // expect contract to pass
    BOOST_CHECK_NO_THROW(account(10));

    // expect precondition to fail
    test::check_throw_on_contract_violation([] { account(0); },
                                            contract::type::precondition);

    // expect postcondition to fail
    test::check_throw_on_contract_violation([] { account(0, true); },
                                            contract::type::postcondition);
}

// Copyright Alexei Zakharov, 2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
