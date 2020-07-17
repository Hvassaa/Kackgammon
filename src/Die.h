class Die 
{
	private:
		int eyes;
		bool used;
		bool isDoubleRoll;
	public:
		Die();
		int getEyes();
		bool isUsed();
		void setUsed();
		void setUnused();
		void setAsDoubleRoll();
		void rollDie();
		bool isUnusedDouble();
};
