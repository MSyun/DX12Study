template<typename T>
IArchivesType<T>::IArchivesType() {
	Create();
}

template<typename T>
IArchivesType<T>::~IArchivesType() {

}

template<typename T>
T IArchivesType<T>::Get(const string& _name) {
	auto it = archives.find(_name);
	if (it == archives.end()) {
		T val = 0;
		return val;
	}

	return it->second;
}

template<typename T>
void IArchivesType<T>::Add(const string& _key, T _regist) {
	archives.insert(std::pair<string, T>(_key, _regist));
}
