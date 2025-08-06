//
//                   Shree Matraye Namaha
//                   --------------------
// general_exception - C++ General Exception Class Library
//
// Copyright (c) 2025 Rathnadhar K V (Rathnadhar Research RR-->)
//
// Licensed under the MIT License. You may obtain a copy of the License at:
// https://opensource.org/licenses/MIT
//
// This software is provided "as is", without warranty of any kind, express or implied.
// See the License for the specific language governing permissions and limitations.

#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include <limits>
#include <format>
#include <expected>

using ExceptionID           = u_int64_t;
using ExceptionMessage      = std::string;
using ExceptionMessageView  = std::string_view;

//Maxium chars in the message is limited to 256 chars
inline static constexpr std::size_t max_exception_message_size = 256;

//The only time we use a macro...
//Why?
//To complete strip the release build of location information...
//Yes this is a non-standard exception implementation.. but I cannot take chances in exposing the
//location information in a release build.

struct DebugBuildTag {};
struct ReleaseBuildTag {};

#ifdef RELEASE_BUILD
using BuildTag = ReleaseBuildTag;
#define NO_SOURCE_LOCATION
#else

#include <source_location>
using ExceptionLocation     = std::source_location;

using BuildTag = DebugBuildTag;

//create a custom formatter for debug location information.
template<>
struct std::formatter<std::source_location, char>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const std::source_location& loc, std::format_context& ctx) const
    {
        static constexpr std::string_view location_format_template =  "file name: {}, line: {}, function name: {}";

        return std::format_to(ctx.out(),location_format_template,
                              loc.file_name(),
                              loc.line(),
                              loc.function_name()
                             );
    }
};
#endif //of Debug Build

//Exception message will be limited to max_exception_message_size ...
inline static auto limit_exception_message = [](const std::string_view in_exception_message_view) -> std::string
                                                {return(in_exception_message_view.size() <= max_exception_message_size ?
                                                        std::string{in_exception_message_view}:
                                                        std::string{in_exception_message_view.substr(0, max_exception_message_size)}
                                                       );
                                                };

//Defining the class template so as to remove the location information during the release build
template<typename Tag>
class general_exception_base;

template<>
class general_exception_base<ReleaseBuildTag>
{
    protected:
        inline static constexpr std::string_view format_template = "Exception: error_code: {}, error_message: {}";

        ExceptionID      exception_id{std::numeric_limits<ExceptionID>::max()};
        ExceptionMessage exception_message{};

    public:
        general_exception_base() = default;

        general_exception_base(ExceptionID in_exception_id)
                               : exception_id{in_exception_id} {}

        general_exception_base(const ExceptionMessage& in_exception_msg)
                              : exception_message{limit_exception_message(in_exception_msg)} {}

        general_exception_base(ExceptionMessageView in_exception_msg)
                              : exception_message{limit_exception_message(in_exception_msg)} {}

        general_exception_base(ExceptionID             in_exception_id,
                               const ExceptionMessage& in_exception_msg
                              )
                              : exception_id{in_exception_id},
                              exception_message{limit_exception_message(in_exception_msg)} {}

        general_exception_base(ExceptionID          in_exception_id,
                               ExceptionMessageView in_exception_msg
                              )
                              : exception_id{in_exception_id},
                              exception_message{limit_exception_message(in_exception_msg)} {}

        [[nodiscard]] ExceptionMessage what() const noexcept
                                       {
                                           return std::format(format_template,
                                                              this->exception_id,
                                                              this->exception_message
                                                             );
                                       }

        [[nodiscard]] ExceptionID id() const noexcept
                                  {
                                      return this->exception_id;
                                  }

        [[nodiscard]] ExceptionMessageView message() const noexcept
                                           {
                                               return this->exception_message;
                                           }
};

//Exception for Debug build, this has error location information.
template<>
class general_exception_base<DebugBuildTag>
{
    protected:
        inline static constexpr std::string_view format_template   = "Exception: error_code: {}, error_message: {}, {}";
        inline static constexpr std::string_view loc_format_string = "{}";

        ExceptionID       exception_id{std::numeric_limits<ExceptionID>::max()};
        ExceptionMessage  exception_message{};
        ExceptionLocation exception_location;

    public:
        general_exception_base(std::source_location in_exception_location = std::source_location::current())
                              : exception_location{in_exception_location} {}

        general_exception_base(ExceptionID          in_exception_id,
                               std::source_location in_exception_location = std::source_location::current()
                              )
                              : exception_id{in_exception_id},
                                exception_location{in_exception_location} {}

        general_exception_base(const ExceptionMessage& in_exception_msg,
                               std::source_location    in_exception_location = std::source_location::current()
                              )
                              : exception_message{limit_exception_message(in_exception_msg)},
                                exception_location{in_exception_location} {}

        general_exception_base(const ExceptionMessageView in_exception_msg,
                               std::source_location       in_exception_location = std::source_location::current()
                              )
                              : exception_message{limit_exception_message(in_exception_msg)},
                                exception_location{in_exception_location} {}

        general_exception_base(ExceptionID             in_exception_id,
                               const ExceptionMessage& in_exception_msg,
                               std::source_location    in_exception_location = std::source_location::current()
                              )
                              : exception_id{in_exception_id},
                                exception_message{limit_exception_message(in_exception_msg)},
                                exception_location{in_exception_location} {}

        general_exception_base(ExceptionID                in_exception_id,
                               const ExceptionMessageView in_exception_msg,
                               std::source_location       in_exception_location = std::source_location::current()
                              )
                              : exception_id{in_exception_id},
                                exception_message{limit_exception_message(in_exception_msg)},
                                exception_location{in_exception_location} {}

    [[nodiscard]] ExceptionMessage what() const noexcept
                                   {
                                       return std::format(format_template,
                                                          this->exception_id,
                                                          exception_message,
                                                          std::format(loc_format_string, exception_location)
                                                         );
                                   }

    [[nodiscard]] ExceptionID id() const noexcept
                              {
                                  return this->exception_id;
                              }

   [[nodiscard]] ExceptionMessageView message() const noexcept
                                      {
                                          return this->exception_message;
                                      }

   [[nodiscard]] ExceptionLocation location() const noexcept
                                   {
                                      return this->exception_location;
                                   }
};

namespace general_exception
{
    class general_exception : public general_exception_base<BuildTag>
    {
        using Base = general_exception_base<BuildTag>;

        public:
            general_exception() = default;

            general_exception(ExceptionID in_exception_id)
                             : Base{in_exception_id} {}

            general_exception(const ExceptionMessage& in_exception_msg)
                             : Base{in_exception_msg} {}

             general_exception(const ExceptionMessageView in_exception_msg)
                              : Base{in_exception_msg} {}

             general_exception(ExceptionID                in_exception_id,
                               const ExceptionMessageView in_exception_msg
                              )
                              : Base{in_exception_id,
                                     in_exception_msg
                                    } {}

#ifndef RELEASE_BUILD
             general_exception(ExceptionMessageView in_exception_msg,
                               std::source_location in_exception_location
                              )
                              : Base{in_exception_msg,
                                     in_exception_location
                                    } {}

             general_exception(ExceptionID          in_exception_id,
                               ExceptionMessageView in_exception_msg,
                               std::source_location in_exception_location
                              )
                              : Base{in_exception_id,
                                     in_exception_msg,
                                     in_exception_location
                                    } {}
             using Base::location;
#endif

             using Base::what;
             using Base::id;
             using Base::message;
    };

    using GENERAL_EXCEPTION_EXPECTED_VOID_RETURN    =   std::expected<void,general_exception>;
}

