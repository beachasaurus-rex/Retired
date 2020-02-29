using System;
using System.Windows.Input;
using Microsoft.WindowsAPICodePack.Dialogs;
using GucciFinances.Models.Commands;
using GucciFinances.Models.MySql.DatabaseObjects.Gateways;
using GucciFinances.Models.DatabaseObjects.Records;
using GucciFinances.Models.Enums;
using GucciFinances.Views.Forms;

namespace GucciFinances.Models.Controllers
{
    public class TransactionFormsController
    {
        #region Fields

        private readonly PostTransactionForm _transPostForm;
        private readonly MySqlTransactionGateway _transGate;

        private ICommand _getDocDir;
        private ICommand _postTrans;

        #endregion Fields

        #region Properties

        public ICommand GetDocFolder
        {
            get
            {
                if (_getDocDir == null)
                {
                    _getDocDir = new RelayCommand(
                        param => GetDocFolderPath()
                        );
                }
                return _getDocDir;
            }
        }
        public ICommand PostTransaction
        {
            get
            {
                if (_postTrans == null)
                {
                    _postTrans = new RelayCommand(
                        param => PostTransactionRecord()
                        );
                }
                return _postTrans;
            }
        }

        #endregion Properties

        #region Constructors

        public TransactionFormsController(PostTransactionForm transPostForm)
        {
            _transPostForm = transPostForm;
            _transGate = new MySqlTransactionGateway();
        }

        #endregion Constructors

        #region Private Helpers

        private void GetDocFolderPath()
        {
            using (CommonOpenFileDialog dlg = new CommonOpenFileDialog())
            {
                dlg.Title = "Folder Dialog";
                dlg.IsFolderPicker = true;

                dlg.AddToMostRecentlyUsedList = false;
                dlg.AllowNonFileSystemItems = false;
                dlg.EnsureFileExists = true;
                dlg.EnsurePathExists = true;
                dlg.EnsureReadOnly = false;
                dlg.EnsureValidNames = true;
                dlg.Multiselect = false;
                dlg.ShowPlacesList = true;

                if (dlg.ShowDialog() == CommonFileDialogResult.Ok)
                {
                    string folder = dlg.FileName;
                    _transPostForm.txtbxDirPath.Text = folder + @"\";
                }
            }
        }

        //TODO: make this and finish the transaction form
        private void PostTransactionRecord()
        {
            //make helper for collecting page info
            //create transaction record with info
            //post record using gateway

            //all in a 1-liner baby WOO!!!!!
            _transGate.Post(GetPostFormData());
        }

        private TransactionRecord GetPostFormData()
        {
            //these must be converted or else c# complains
            double amount = double.Parse(_transPostForm.txtbxAmount.Text);
            DateTime date = _transPostForm.dtpkrDate.SelectedDate ?? DateTime.Now;
            bool work = _transPostForm.chkbxIsWork.IsChecked ?? false;
            bool sub = _transPostForm.chkbxIsSubscription.IsChecked ?? false;
            PaymentMethod mop = (PaymentMethod)_transPostForm.cmboMop.SelectedItem;
            string dirPath = _transPostForm.txtbxDirPath.Text;
            dirPath = dirPath.Replace("\\", "\\\\");

            int workInt = 0;
            int subInt = 0;

            if (work)
            {
                workInt = 1;
            }
            if (sub)
            {
                subInt = 1;
            }

            TransactionRecord transRec = new TransactionRecord(_transPostForm.txtbxMerchant.Text,
                                                               amount,
                                                               workInt,
                                                               subInt,
                                                               date,
                                                               mop,
                                                               _transPostForm.txtbxCardName.Text,
                                                               dirPath,
                                                               _transPostForm.txtbxComment.Text);

            return transRec;
        }

        #endregion Private Helpers
    }
}
