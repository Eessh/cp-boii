//
// Created by eessh on 03-05-2023.
//

#ifndef CP_BOII_RESULT_HPP
#define CP_BOII_RESULT_HPP

#include <memory>
#include <variant>

template <typename T>
class Ok
{
public:
  explicit constexpr Ok(T value) : value(std::move(value)) {}

  constexpr T&& take_value()
  {
    return std::move(value);
  }

  T value;
};

template <typename T>
class Error
{
public:
  explicit constexpr Error(T value) : value(std::move(value)) {}

  constexpr T&& take_value()
  {
    return std::move(value);
  }

  T value;
};

template <typename OkT, typename ErrorT>
class Result
{
public:
  constexpr Result(Ok<OkT> value) : variant(std::move(value)) {}
  constexpr Result(Error<ErrorT> value) : variant(std::move(value)) {}

  [[nodiscard]] constexpr bool ok() const
  {
    return std::holds_alternative<Ok<OkT>>(variant);
  }

  [[nodiscard]] constexpr bool error() const
  {
    return std::holds_alternative<Error<ErrorT>>(variant);
  }

  [[nodiscard]] constexpr OkT ok_value() const
  {
    return std::get<Ok<OkT>>(variant).value;
  }

  [[nodiscard]] constexpr ErrorT error_value() const
  {
    return std::get<Error<ErrorT>>(variant).value;
  }

  constexpr OkT&& take_ok_value()
  {
    return std::get<Ok<OkT>>(variant).take_value();
  }

  constexpr ErrorT&& take_error_value()
  {
    return std::get<Error<ErrorT>>(variant).take_value();
  }

  std::variant<Ok<OkT>, Error<ErrorT>> variant;
};

#endif //CP_BOII_RESULT_HPP
