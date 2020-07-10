class Die 
{
	private:
		int eyes;
		bool used;
	public:
		Die();
		int getEyes();
		bool isUsed();
		void setUsed();
		void setUnused();
		void rollDie();
};
