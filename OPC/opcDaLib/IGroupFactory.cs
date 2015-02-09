using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace opcDaLib
{
    /// <summary>
    /// Group factory interface
    /// </summary>
    /// <remarks>
    /// Abstracts group creation and storage
    /// </remarks>
    interface IGroupFactory
    {
        /// <summary>
        /// Creates a new group and registers it in a group
        /// </summary>
        /// <exception cref="NameConflictException">Thrown if the group with this name already exists</exception>
        /// <param name="Name">Grop name</param>
        /// <param name="bActive">Active status</param>
        /// <param name="dwRequestedUpdateRate">Requested update rate</param>
        /// <param name="hClientGroup">Client group handle</param>
        /// <param name="pTimeBias">Time bias</param>
        /// <param name="pPercentDeadband">Deadband</param>
        /// <param name="dwLCID">Language ID</param>
        /// <returns>Newly created group object</returns>
        Group CreateGroup(string Name, int bActive, int dwRequestedUpdateRate, int hClientGroup, int pTimeBias, float pPercentDeadband, int dwLCID);
        /// <summary>
        /// Returns group by its name
        /// </summary>
        /// <param name="Name">Group name</param>
        /// <returns>Group object. Null if such group does not exist</returns>
        Group GetGroup(string Name);
        /// <summary>
        /// Removes ze group by its server handle
        /// </summary>
        /// <remarks>
        /// Apart from un-registering the group from the factory, it also marks the group
        /// as deleted so any calls to it that may follow will fail
        /// </remarks>
        /// <param name="serverHandle">group server handle</param>
        void RemoveGroup(int serverHandle);
    }
}
