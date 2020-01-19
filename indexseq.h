#ifndef INDEXSEQ_H
#define INDEXSEQ_H
////////////////////////////////////
//这个是用来生成整数序列类型的
////example:  MakeIndexes<3>::type   == IndexSeq<0,1,2>
//整型序列的定义
template<int...>
struct IndexSeq{};

//继承方式，开始展开参数包
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// 模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};
#endif // INDEXSEQ_H
