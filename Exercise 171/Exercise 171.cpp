class C_Problem171
{
protected :

	int m_NDigits, m_NLastDigits ;
	unsigned __int64 m_Factorials [Problem171_MaxDigits + 1] ;
	unsigned __int64 m_Digits [Problem171_MaxDigits] ;
	unsigned __int64 m_NOfEachFace [Problem171_MaxDigits] ;
	unsigned __int64 m_DigitsSquared [10] ;
	unsigned __int64 m_PowerOf10ForLastDigits ;
	unsigned __int64 m_AllOnes ;

	static bool IsSquare (__int64 Num)
	{
		__int64 Sqrt = (__int64) (sqrt ((double) Num)) ;
		return (Num == Sqrt * Sqrt) ;
	} ;

	static __int64 GCD (__int64 a, __int64 b)
	{
		if (b == 0) { return a ; }
		else { return GCD (b, a % b) ; }
	} ;

	C_Problem171 (int NDigits, int NLastDigits)
	{
		m_NDigits = NDigits ;
		m_NLastDigits = NLastDigits ;

		if (m_NDigits >= m_NLastDigits && m_NDigits > 0 && m_NLastDigits > 0 && 
			m_NDigits <= Problem171_MaxDigits &&
			m_NLastDigits <= Problem171_MaxLastDigits)
		{
			for (int i = 0 ; i < 10 ; i ++)
			{
				m_DigitsSquared [i] = i * i ;
			}

			m_PowerOf10ForLastDigits = 1 ;

			for (int i = 1 ; i <= m_NLastDigits ; i ++)
			{
				m_PowerOf10ForLastDigits *= 10 ;
			}

			m_AllOnes = 1 ;

			for (int i = 1 ; i <= m_NLastDigits ; i ++)
			{
				m_AllOnes *= 10 ;
			}

			m_AllOnes = (m_AllOnes - 1) / 9 ;

			m_Factorials [0] = 1 ;

			for (int i = 1 ; i <= m_NDigits ; i ++)
			{
				m_Factorials [i] = i * m_Factorials [i - 1] ;
			}
		}
		else
		{
			m_NDigits = 0 ;
		}
	} ;

	bool CreatedOK () const
	{
		return m_NDigits > 0 ;
	} ;

	unsigned __int64 DoCountAndSum (
		unsigned __int64 & SumLastDigits, 
		int ThisDigitIndex, 
		unsigned __int64 DigitSumSoFar, 
		unsigned __int64 DigitSqSumSoFar, 
		int NUnique)
	{
		unsigned __int64 RetVal = 0 ;

		if (ThisDigitIndex == m_NDigits)
		{
			if (IsSquare (DigitSqSumSoFar))
			{
				unsigned __int64 Denom = 1 ;

				for (unsigned __int64 i = 0 ; i < NUnique ; i ++)
				{
					Denom *= m_Factorials [m_NOfEachFace [i]] ;
				}

				RetVal = m_Factorials [m_NDigits] / Denom ;

				unsigned __int64 SumAllDigits = DigitSumSoFar ;
				unsigned __int64 CommonFactor = GCD (m_Factorials [m_NDigits - 1], Denom) ;
				unsigned __int64 Mult = m_Factorials [m_NDigits - 1] / CommonFactor ;

				Denom /= CommonFactor ;

				CommonFactor = GCD (SumAllDigits, Denom) ;

				if (CommonFactor > 1)
				{
					SumAllDigits /= CommonFactor ;
					Denom /= CommonFactor ;
				}

				SumAllDigits *= Mult ;
				SumAllDigits /= Denom ;
				SumAllDigits %= m_PowerOf10ForLastDigits ;
				SumAllDigits *= m_AllOnes ;

				SumLastDigits += SumAllDigits ;
				SumLastDigits %= m_PowerOf10ForLastDigits ;
			}
		}
		else
		{
			bool StartSameAsLast = ThisDigitIndex > 0 ;
			int MinDigit = StartSameAsLast ? m_Digits [ThisDigitIndex - 1] : 0 ;

			for (int i = MinDigit ; i < 10 ; i ++)
			{
				if (StartSameAsLast)
				{
					m_NOfEachFace [NUnique - 1] ++ ;
				}
				else
				{
					m_NOfEachFace [NUnique ++] = 1 ;
				}

				m_Digits [ThisDigitIndex] = i ;
				RetVal += DoCountAndSum (
					SumLastDigits, 
					ThisDigitIndex + 1, 
					DigitSumSoFar + i, 
					DigitSqSumSoFar + m_DigitsSquared [i], 
					NUnique) ;

				if (StartSameAsLast)
				{
					m_NOfEachFace [NUnique - 1] -- ;
					StartSameAsLast = false ;
				}
				else
				{
					NUnique -- ;
				}
			}
		}

		return RetVal ;
	} ;

public :

	static C_Problem171 * Create (int NDigits, int NLastDigits)
	{
		C_Problem171 * RetVal = new C_Problem171 (NDigits, NLastDigits) ;

		if (RetVal)
		{
			if (! RetVal->CreatedOK ())
			{
				delete RetVal ;
				RetVal = NULL ;
			}
		}
		return RetVal ;
	} ;

	unsigned __int64 CountAndSum (unsigned __int64 & SumLastDigits)
	{
		SumLastDigits = 0 ;

		return DoCountAndSum (SumLastDigits, 0, 0, 0, 0) ;
	} ;

	static void Solve ()
	{
		const int NDigits = Problem171_MaxDigits ;
		const int NLastDigits = Problem171_MaxLastDigits ;
		CString Str ;
		C_Problem171 * P171 = C_Problem171::Create (NDigits, NLastDigits) ;

		if (P171)
		{
			clock_t StartTime = clock () ;
			unsigned __int64 SumLastDigits, Count = P171->CountAndSum (SumLastDigits) ;
			clock_t TotalTime = clock () - StartTime ;

			Str.Format ("%I64d Numbers - Sum Last Digits: %I64d (%ldms)", Count, SumLastDigits, TotalTime) ;
			// "2130015017428935930 Numbers - Sum Last Digits: 142989277 (711ms)"

			delete P171 ;
		}
		else
		{
			Str = "Error creating problem object" ;
		}
		AfxMessageBox (Str, MB_OK) ;
	} ;
} ;