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

#include "du_slice_ric_configuration_procedure.h"
#include "srsran/ran/band_helper.h"
#include "srsran/support/async/execute_on_blocking.h"

using namespace srsran;
using namespace srs_du;

du_slice_ric_configuration_procedure::du_slice_ric_configuration_procedure(const du_mac_sched_control_config& request_,
                                                                           fifo_async_task_scheduler*  main_ctrl_loop_,
                                                                           const du_manager_params&         du_params_) :
  request(request_), main_ctrl_loop(main_ctrl_loop_), du_params(du_params_)
{
}

void du_slice_ric_configuration_procedure::operator()(coro_context<async_task<du_mac_sched_control_config_response>>& ctx)
{
  CORO_BEGIN(ctx);

  CORO_AWAIT(execute_on_blocking(du_params.services.du_mng_exec, du_params.services.timers));

  CORO_AWAIT(dispatch_slice_config_task());

  CORO_RETURN(slice_config_completed.get());
}

manual_event<du_mac_sched_control_config_response>& du_slice_ric_configuration_procedure::dispatch_slice_config_task() {
  main_ctrl_loop->schedule(launch_async([this](coro_context<async_task<void>>& ctx) {
      bool result;
      CORO_BEGIN(ctx);
      CORO_AWAIT_VALUE(result, handle_slice_config());
      slice_config_completed.set(du_mac_sched_control_config_response{result, result, result});
      CORO_RETURN();
  }));

  return slice_config_completed;
}

async_task<bool> du_slice_ric_configuration_procedure::handle_slice_config() {
  control_config_params control_config_params = request.param_list[0]; // TODO: loop over each control config param
  du_cell_index_t cell_index = MIN_DU_CELL_INDEX;
  return du_params.mac.ue_cfg.handle_slice_reconfiguration_request(cell_index, control_config_params.rrm_policy_group.value());
}