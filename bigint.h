//create, destory, resize
BigInt* newBigInt(int size);
BigInt* newBigInt_int(int value);
BigInt* newBigInt_long(long value);
BigInt* copyBigInt(BigInt *bigInt);
void freeBigInt(BigInt *bigInt);
void resizeBigInt(BigInt *bigInt, unsigned int newSize);
void autoResizeBigInt(BigInt *bigInt);


//comparsion methods
bool eqMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool eqBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool isZeroBigInt(BigInt *bigInt);

//basic operation
void incMagBigInt(BigInt *bigInt);
void decMagBigInt(BigInt *bigInt);
void incBigInt(BigInt *bigInt);
void decBigInt(BigInt *bigInt);

//mutable operations, first argument gets mutation
void addMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
void subMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
void addBigInt(BigInt *bigInt1, BigInt *bigInt2);
void subBigInt(BigInt *bigInt1, BigInt *bigInt2);
void mulBigInt(BigInt *bigInt1, BigInt *bigInt2);
void divBigInt(BigInt *bigInt1, BigInt *bigInt2);


//immutable operations, creates new object
BigInt* addMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* addBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* mulBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* divBigInt_new(BigInt *bigInt1, BigInt *bigInt2);


