using System;
using System.Windows.Input;
using System.Diagnostics;

namespace GucciFinances.Models.Commands
{
    /// <summary>
    /// A command whose sole purpose is to relay its
    /// functionality to other objects by invoking
    /// delegates. The default return value for the
    /// CanExecute method is 'true'.
    /// </summary>
    public class RelayCommand : ICommand
    {
        #region Fields

        //This is a method that will perform the
        //requested action.
        readonly Action<object> _execute;

        //This is a method that will determine
        //if _execute SHOULD execute.
        readonly Predicate<object> _canExecute;

        #endregion Fields

        #region Constructors

        /// <summary>
        /// Creates a new command that can always
        /// execute.
        /// </summary>
        /// <param name="execute">The execution logic.</param>

        //This constructor should be used when you know
        //absolutely positively that the delegate should
        //execute.
        public RelayCommand(Action<object> execute)
            : this(execute, null)
        {
        }

        /// <summary>
        /// Creates a new command.
        /// </summary>
        /// <param name="execute">The execution logic.</param>
        /// <param name="canExecute">The execution stats logic.</param>

        //This constructor should be used when you know which delegate you want
        //to execute and when you have a different delegate to determine if
        //your command should execute.
        public RelayCommand(Action<object> execute, Predicate<object> canExecute)
        {
            //if (execute != null)
            //{
            //    _execute = execute;
            //}
            //else 
            //{
            //    throw new ArgumentNullException("execute");
            //}

            //The next line is equivalent to the above code.
            _execute = execute ?? throw new ArgumentNullException("execute");
            _canExecute = canExecute;
        }

        #endregion Constructors

        #region ICommand Members

        /// <summary>
        /// Determines if the command is able to be executed.
        /// </summary>
        /// <param name="parameters">Input parameters for Predicate.</param>
        /// <returns></returns>
        [DebuggerStepThrough]
        public bool CanExecute(object parameters)
        {
            //if (_canExecute == null)
            //{
            //    return true;
            //}
            //else
            //{
            //    return _canExecute(parameters);
            //}

            //The next line is equivalent to the above code.
            return _canExecute == null ? true : _canExecute(parameters);
        }

        /// <summary>
        /// This is used to notify that the CanExecute property has changed.
        /// </summary>
        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        /// <summary>
        /// Executes the command.
        /// </summary>
        /// <param name="parameters">Input parameters for Action.</param>
        public void Execute(object parameters)
        {
            _execute(parameters);
        }

        #endregion ICommand Members
    }
}

