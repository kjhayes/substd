#ifndef SS_TEMPLATE_HPP
#define SS_TEMPLATE_HPP

#define CRTP_ASSERT(class, self) static_assert(std::is_base_of<class<self>, self>(), "CRTP ASSERT FAILURE")

#endif//SS_TEMPLATE_HPP