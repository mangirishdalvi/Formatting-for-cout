#include <tuple>
#include <string>
#include <iostream>
#include <type_traits>
#include <ios>
#include <algorithm>
#include <array>
#include <iomanip>

struct WrongNumberOfArgs
{

};

auto ffr(std::basic_ostream<char, std::char_traits<char>>& (*fp)(std::basic_ostream<char, std::char_traits<char>>&))
{
	return fp;
}

template <typename ...Types>
class Printer
{
	const char *fmt;
	std::tuple<const Types&...> args;
public:
	Printer(const char *s,const Types&... types):fmt(s),args(types...){}

	friend std::ostream &operator<<(std::ostream &out,Printer<Types...> printer)
	{
		return printer.helper(out,&printer.fmt,std::make_index_sequence<std::tuple_size<decltype(printer.args)>::value>{});	
	}

private:
	template <size_t...Ns>
	std::ostream &helper(std::ostream &out,const char **fmt,std::index_sequence<Ns...>) 
	{
		print_func(out,fmt,std::get<Ns>(args)...);
		return out;
	}

	void print_func(std::ostream &out,const char **fmt) const
	{
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;
			}
			else
			{
				throw WrongNumberOfArgs();
			}
		}
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::ostream& (*func)(std::ostream&), const Tail& ... rest) const
	{
		static std::array<std::ostream& (*)(std::ostream&),2> consume_cat={ffr(std::ends),ffr(std::endl)};
		out<<func;
		if((std::find(consume_cat.begin(),consume_cat.end(),func)!=consume_cat.end()))
		{
			(*fmt)++;
		}
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::ios_base&(*func)(std::ios_base&), const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Setprecision func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Resetiosflags func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Setiosflags func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Setbase func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	
	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Setfill<char> func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}
	
	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Setw func, const Tail& ... rest) const
	{
		out<<func;
		print_func(out,fmt,rest...);
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Put_money<long double> func, const Tail& ... rest) const
	{
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;
			}
			else
			{
				out<<func;
				(*fmt)++;
				print_func(out,fmt,rest...);
			}
		}
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Put_money<std::string> func, const Tail& ... rest) const
	{
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;
			}
			else
			{
				out<<func;
				(*fmt)++;
				print_func(out,fmt,rest...);
			}
		}
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::_Put_time<char> func, const Tail& ... rest) const
	{
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;
			}
			else
			{
				out<<func;
				(*fmt)++;
				print_func(out,fmt,rest...);
			}
		}
	}

	template <typename ... Tail>
	void print_func(std::ostream &out,const char **fmt,std::__detail::_Quoted_string<char const*, char> func, const Tail& ... rest) const
	{
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;
			}
			else
			{
				out<<func;
				(*fmt)++;	
				print_func(out,fmt,rest...);
			}
		}
	}

	

	template <typename Head, typename ... Tail>
	typename std::enable_if<!std::is_same<Head,std::ios_base&(std::ios_base&)>::value&&
							!std::is_same<Head,std::_Setprecision>::value>::type
	print_func(std::ostream &out,const char **fmt,const Head& h,const Tail& ... rest) const
	{
		if((**fmt)=='\0')
		{
			throw WrongNumberOfArgs();
		}
		
		while((**fmt)!='\0')
		{
			if((**fmt)=='\\'&&((*((*fmt)+1))=='%'))
			{
				out<<(*((*fmt)+1));
				(*fmt)+=2;
			}
			else if((**fmt)!='%')
			{
				out<<(**fmt);
				(*fmt)++;	
			}
			else
			{
				out<<h;
				(*fmt)++;
				print_func(out,fmt,rest...);
			}
		}
	}

};

template <typename ...Types>
Printer<Types...> Interpolate(const char *fmt,const Types&... types)
{
	return Printer<Types...>(fmt,types...);
}