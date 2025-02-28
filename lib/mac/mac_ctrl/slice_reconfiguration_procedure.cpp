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

#include "slice_reconfiguration_procedure.h"
#include "mac_config.h"
#include "mac_scheduler_configurator.h"
#include "proc_logger.h"

using namespace srsran;

mac_slice_reconfiguration_procedure::mac_slice_reconfiguration_procedure(du_cell_index_t                 cell_index_,
                                                                   const rrm_policy_ratio_group          reconf_,
                                                                   mac_control_config&                   cfg_,
                                                                   mac_ul_configurator&                  mac_ul_,
                                                                   mac_dl_configurator&                  mac_dl_,
                                                                   mac_scheduler_configurator&           sched_cfg_) :
  cell_index(cell_index_), reconf(reconf_), cfg(cfg_), logger(cfg.logger), ul_unit(mac_ul_), dl_unit(mac_dl_), sched_cfg(sched_cfg_)
{
}

void mac_slice_reconfiguration_procedure::operator()(coro_context<async_task<bool>>& ctx)
{
  CORO_BEGIN(ctx);
  
  CORO_AWAIT_VALUE(sched_conf_res, sched_cfg.handle_slice_reconfiguration_request(cell_index, reconf));

  CORO_RETURN(handle_result(sched_conf_res));
}

bool mac_slice_reconfiguration_procedure::handle_result(bool result)
{
  return result;
}
