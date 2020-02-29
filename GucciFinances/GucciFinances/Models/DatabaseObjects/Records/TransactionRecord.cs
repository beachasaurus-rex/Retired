using System;
using GucciFinances.Models.Enums;

namespace GucciFinances.Models.DatabaseObjects.Records
{
    public class TransactionRecord : Record
    {
        #region Fields

        private string _merchant;
        private double _amount;
        private int _isWork;
        private DateTime _date;
        private string _comment;
        private string _payMethod;
        private string _cardName;
        private int _isSubscription;
        private string _docFolderPath;

        #endregion Fields

        #region Properties

        public override int? ID { get { return _id; } }
        public string Merchant { get { return _merchant; } }
        public double Amount { get { return _amount; } }
        public int IsWork { get { return _isWork; } }
        public DateTime TransactionDate { get { return _date; } }
        public string Comment { get { return _comment; } }
        public string MethodOfPayment { get { return _payMethod; } }
        public string CardName { get { return _cardName; } }
        public int IsSubscription { get { return _isSubscription; } }
        public string DocumentFolderPath { get { return _docFolderPath; } }

        #endregion Properties

        //constructor
        /// <summary>
        /// This represents a specific transaction record.
        /// </summary>
        /// <param name="merchant"></param>
        /// <param name="amount"></param>
        /// <param name="isWork"></param>
        /// <param name="isSubscription"></param>
        /// <param name="dateTime"></param>
        /// <param name="payMethod"></param>
        /// <param name="cardName"></param>
        /// <param name="docFolderPath"></param>
        /// <param name="comment"></param>
        /// <param name="id"></param>
        public TransactionRecord(string merchant,
                                 double amount,
                                 int isWork,
                                 int isSubscription,
                                 DateTime dateTime,
                                 PaymentMethod payMethod,
                                 string cardName = "",
                                 string docFolderPath = "",
                                 string comment = "",
                                 int? id = null)
        {
            //assign properties
            _merchant = merchant;
            _amount = amount;
            _isWork = isWork;
            _isSubscription = isSubscription;
            _date = dateTime.Date;
            _payMethod = payMethod.ToString();
            _cardName = cardName;
            _docFolderPath = docFolderPath;
            _comment = comment;
            _id = id;
        }
    }
}
