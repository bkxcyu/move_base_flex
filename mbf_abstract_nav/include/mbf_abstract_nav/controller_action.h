/*
 *  Copyright 2018, Magazino GmbH, Sebastian Pütz, Jorge Santos Simón
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  controller_action.h
 *
 *  authors:
 *    Sebastian Pütz <spuetz@uni-osnabrueck.de>
 *    Jorge Santos Simón <santos@magazino.eu>
 *
 */

#ifndef MBF_ABSTRACT_NAV__CONTROLLER_ACTION_H_
#define MBF_ABSTRACT_NAV__CONTROLLER_ACTION_H_

#include "mbf_abstract_nav/abstract_action.h"
#include "mbf_abstract_nav/abstract_controller_execution.h"
#include "mbf_abstract_nav/robot_information.h"
#include <actionlib/server/action_server.h>
#include <mbf_msgs/ExePathAction.h>

namespace mbf_abstract_nav{

class ControllerAction :
    public AbstractAction<mbf_msgs::ExePathAction, AbstractControllerExecution>
{
 public:

  typedef boost::shared_ptr<ControllerAction> Ptr;

  ControllerAction(const std::string &name,
                   const RobotInformation &robot_info);

  void start(
      GoalHandle goal_handle,
      typename AbstractControllerExecution::Ptr execution_ptr
  );

  void run(GoalHandle &goal_handle, AbstractControllerExecution &execution);

protected:
  void publishExePathFeedback(
          GoalHandle& goal_handle,
          const geometry_msgs::PoseStamped& robot_pose,
          const geometry_msgs::PoseStamped& goal_pose,
          uint32_t outcome, const std::string &message,
          const geometry_msgs::TwistStamped& current_twist);

  /**
   * @brief Utility method to fill the ExePath action result in a single line
   * @param robot_pose Current pose of the robot
   * @param goal_pose Robot's goal pose
   * @param outcome ExePath action outcome
   * @param message ExePath action message
   * @param result The action result to fill
   */
  void fillExePathResult(
        const geometry_msgs::PoseStamped& robot_pose,
        const geometry_msgs::PoseStamped& goal_pose,
        uint32_t outcome, const std::string &message,
        mbf_msgs::ExePathResult &result);

};
}



#endif //MBF_ABSTRACT_NAV__CONTROLLER_ACTION_H_
