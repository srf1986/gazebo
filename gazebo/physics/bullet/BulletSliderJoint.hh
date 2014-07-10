/*
 * Copyright (C) 2012-2014 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _BULLETSLIDERJOINT_HH_
#define _BULLETSLIDERJOINT_HH_
#include <ignition/math/Angle.hh>
#include <ignition/math/Vector3.hh>
#include "gazebo/physics/bullet/BulletJoint.hh"
#include "gazebo/physics/SliderJoint.hh"
#include "gazebo/physics/bullet/BulletPhysics.hh"
#include "gazebo/util/system.hh"

class btSliderConstraint;

namespace gazebo
{
  namespace physics
  {
    /// \ingroup gazebo_physics
    /// \addtogroup gazebo_physics_bullet Bullet Physics
    /// \{

    /// \brief A slider joint
    class GAZEBO_VISIBLE BulletSliderJoint : public SliderJoint<BulletJoint>
    {
      /// \brief Constructor
      public: BulletSliderJoint(btDynamicsWorld *world, BasePtr _parent);

      /// \brief Destructor
      public: virtual ~BulletSliderJoint();

      /// \brief Load the BulletSliderJoint
      protected: virtual void Load(sdf::ElementPtr _sdf);

      // Documentation inherited.
      protected: virtual void Init();

      // Documentation inherited.
      public: virtual void SetAxis(unsigned int _index,
                  const ignition::math::Vector3d &_axis);

      // Documentation inherited.
      public: virtual void SetDamping(unsigned int _index,
                  const double _damping);

      // Documentation inherited.
      public: virtual bool SetHighStop(unsigned int _index,
                  const ignition::math::Angle &_angle);

      // Documentation inherited.
      public: virtual bool SetLowStop(unsigned int _index,
                  const ignition::math::Angle &_angle);

      // Documentation inherited.
      public: virtual ignition::math::Angle GetHighStop(unsigned int _index);

      // Documentation inherited.
      public: virtual ignition::math::Angle GetLowStop(unsigned int _index);

      // Documentation inherited.
      public: virtual double GetVelocity(unsigned int _index) const;

      // Documentation inherited.
      public: virtual void SetVelocity(unsigned int _index, double _angle);

      // Documentation inherited.
      public: virtual void SetMaxForce(unsigned int _index, double _force);

      // Documentation inherited.
      public: virtual double GetMaxForce(unsigned int _index);

      // Documentation inherited.
      public: virtual ignition::math::Vector3d GetGlobalAxis(unsigned int _index) const;

      // Documentation inherited.
      public: virtual ignition::math::Angle GetAngleImpl(unsigned int _index) const;

      // Documentation inherited.
      protected: virtual void SetForceImpl(unsigned int _index, double _effort);

      /// \brief Pointer to bullet slider constraint
      private: btSliderConstraint *bulletSlider;

      /// \brief Initial value of joint axis, expressed as unit vector
      ///        in world frame.
      private: ignition::math::Vector3d initialWorldAxis;
    };

  /// \}
  }
}
#endif
