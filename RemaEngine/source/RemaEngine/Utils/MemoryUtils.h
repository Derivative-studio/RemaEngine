/**
 * @file RemaEngine/Utils/MemoryUtils.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-21
 * @copyright Copyright (c) 2023
 *
 * This file is part of RemaEngine.
 *
 * RemaEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RemaEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/

#include <EASTL/shared_ptr.h>
#include <EASTL/safe_ptr.h>
#include <EASTL/linked_ptr.h>
#include <EASTL/unique_ptr.h>

#include <memory>
#include <xmemory>

#ifndef REMA_MEMORYUTILS_H
#define REMA_MEMORYUTILS_H

namespace RemaEngine
{
    /**
    * @brief dynamic_pointer_cast implementation for eastl::shared_ptr
    * @details Returns a copy of a_pEastlPointer ot the proper type
    * with its stored pointer caster dynamically from _Ty1* to _Ty2*.
    * @param[in] a_pEastlPointer - eastl shared pointer.
    * @returns A eastl::shared_ptr object that owns the same pointer
    * as a_pEastlPointer (if any) and has a shared_pointer that points
    * to the same object as a_pEastlPointer with a potentially
    * different type
    **/
    template<typename _Ty1, typename _Ty2>
    eastl::shared_ptr<_Ty1> eastl_dynamic_pointer_cast(const eastl::shared_ptr<_Ty2>& a_pEastlPointer) noexcept
    {
        const auto ptr = dynamic_cast<typename eastl::shared_ptr<_Ty1>::element_type*>(a_pEastlPointer.get());
        if (ptr) {
            return eastl::shared_ptr<_Ty1>(a_pEastlPointer, ptr);
        }

        return {};
    }

    /**
    * @brief dynamic_pointer_cast implementation for eastl::shared_ptr
    * @details Returns a copy of a_pEastlPointer ot the proper type
    * with its stored pointer caster dynamically from _Ty1* to _Ty2*.
    * @param[in] a_pEastlPointer - eastl shared pointer.
    * @returns A eastl::shared_ptr object that owns the same pointer
    * as a_pEastlPointer (if any) and has a shared_pointer that points
    * to the same object as a_pEastlPointer with a potentially
    * different type
    **/
    template<typename _Ty1, typename _Ty2>
    eastl::shared_ptr<_Ty1> eastl_dynamic_pointer_cast(const eastl::shared_ptr<_Ty2>&& a_pEastlPointer) noexcept
    {
        const auto ptr = dynamic_cast<typename eastl::shared_ptr<_Ty1>::element_type*>(a_pEastlPointer.get());
        if (ptr) {
            return eastl::shared_ptr<_Ty1>(std::move(a_pEastlPointer), ptr);
        }

        return {};
    }

    template<typename _Ty1, typename _Ty2, typename _Del>
    auto eastl_dynamic_pointer_cast(eastl::unique_ptr<_Ty2, _Del>&& a_pEastlPointer) noexcept
    {
        const auto ptr = eastl::unique_ptr<_Ty1, _Del>{ dynamic_cast<_Ty1*>(a_pEastlPointer.get()) };
        if (ptr) {
            std::swap(ptr.get_deleter(), a_pEastlPointer.get_deleter());
            a_pEastlPointer.release();
        }

        return ptr;
    }
}

#endif // !REMA_MEMORYUTILS_H
