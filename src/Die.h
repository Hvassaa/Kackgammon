class Die 
{
	private:
		int eyes;
		bool unused;
	public:
		Die();
		Die(int fixedEyes);
		int getEyes() const;
		bool isUnused();
		void roll();
		void use();
};
