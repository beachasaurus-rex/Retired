using System;
using System.ComponentModel;
using System.Diagnostics;

namespace GucciFinances.Models.ObservableModels
{
    //Purpose: To provide base functionality common to all models.
    public abstract class ObservableModel : INotifyPropertyChanged
    {
        #region INotifyPropertyChanged members

        /// <summary>
        /// Raised when a property on this object has a new value.
        /// </summary>

        //This property is used to notify that another property has
        //changed.
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Raises this object's PropertyChanged event.
        /// </summary>
        /// <param name="propertyName"></param>

        //This method is used to initiate the PropertyChanged event.
        //Whenever a property is changed for whatever reason, you will
        //want the class to notify subscribers to the 
        //PropertyChangedEventHandler that a property on this object
        //has just been changed.
        protected virtual void OnPropertyChanged(string propertyName)
        {
            this.VerifyPropertyName(propertyName);

            if (this.PropertyChanged != null)
            {
                PropertyChangedEventArgs e = new PropertyChangedEventArgs(propertyName);
                this.PropertyChanged(this, e);
            }
        }

        #endregion //INotifyPropertyChanged members

        #region Debugging aides

        /// <summary>
        /// Warns the developer if this object does not have a
        /// public property with the specified name. This method does not
        /// exist in a release build.
        /// </summary>

        //This method is used during debugging to determine if the
        //class has the public property with the name passed into
        //the method.
        [Conditional("DEBUG")]
        [DebuggerStepThrough]
        public virtual void VerifyPropertyName(string propertyName)
        {
            if (TypeDescriptor.GetProperties(this)[propertyName] == null)
            {
                string msg = String.Format($"Invalid property name: {propertyName}");

                if (this.ThrowOnInvalidPropertyName)
                {
                    throw new Exception(msg);
                }
                else
                {
                    Debug.Fail(msg);
                }
            }
        }

        /// <summary>
        /// Returns whether an exception is thrown, or if a Debug.Fail()
        /// when an invalid property name is passed to the VerifyPropertyName
        /// method. The default value is false, but subclasses used by unit
        /// tests override this property's getter to return true.
        /// </summary>

        //This is basically used only for unit testing so that an
        //exception is thrown instead of a Debug.Fail().
        protected virtual bool ThrowOnInvalidPropertyName { get; private set; }

        #endregion //Debugging aides
    }
}
