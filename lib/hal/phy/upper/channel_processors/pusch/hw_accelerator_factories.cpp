/*
 *
 * Copyright 2021-2025 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "srsran/hal/phy/upper/channel_processors/pusch/hw_accelerator_factories.h"

using namespace srsran;
using namespace hal;

#ifndef SRSRAN_HAS_ENTERPRISE

std::shared_ptr<hw_accelerator_pusch_dec_factory>
srsran::hal::create_bbdev_pusch_dec_acc_factory(const bbdev_hwacc_pusch_dec_factory_configuration& accelerator_config)
{
  return nullptr;
}

#endif // SRSRAN_HAS_ENTERPRISE
