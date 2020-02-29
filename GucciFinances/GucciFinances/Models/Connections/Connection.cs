using System;

namespace GucciFinances.Models.Connections
{
    public abstract class Connection : IDisposable
    {
        public abstract bool CanConnect { get; }

        public abstract void Connect();
        public abstract void Close();
        public abstract void Dispose();
        public abstract bool IsConnected();
    }
}
