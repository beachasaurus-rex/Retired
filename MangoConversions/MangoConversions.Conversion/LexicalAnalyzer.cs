using System.Collections.Generic;
using MangoConversions.Conversion.UnitSystems;

namespace MangoConversions.Conversion
{
    public static class LexicalAnalyzer
    {
        //TODO: Implement the methods
        public static double GetConversion(string token, UnitSystem fromSource, UnitSystem toTarget)
        {
            List<string> convTokens = GroupConversionTokens(token);
            //double conv = CalculateBaseConversions(convTokens);
            //return CalculateDerivedConversion();
            return 0;
        }

        #region Private Helpers

        /// <summary>
        /// Groups characters into recognizable tokens.
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        public static List<string> GroupConversionTokens(string token)
        {
            List<string> charGroups = new List<string>();
            string curChar = "";
            string groupedChars = "";
            bool storeChars = false;

            for (int i = 0; i < token.Length; i++)
            {
                curChar = token[i].ToString();

                if (curChar == @")")
                {
                    charGroups.Add(groupedChars);
                    groupedChars = "";
                    storeChars = false;
                }

                if ((curChar == @"(") || (storeChars))
                {
                    if (curChar != @"(")
                    {
                        groupedChars = groupedChars + curChar;
                    }
                    else
                    {
                        storeChars = true;
                    }

                }

                if (curChar == @"\")
                {
                    charGroups.Add(curChar);
                }
            }

            return charGroups;
        }

        private static double CalculateBaseConversions(string[] tokens)
        {
            return 0;
        }

        private static double CalculateDerivedConversion()
        {
            return 0;
        }

        #endregion Private Helpers
    }
}
