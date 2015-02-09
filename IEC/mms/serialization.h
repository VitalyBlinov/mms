//-----------------------------------------------------------------------------
// <copyright file="serialization.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 01:25:57</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file MMS protocol PDUs and detail structures serialization routines and placeholders
//-----------------------------------------------------------------------------
#pragma once
#include <type_traits>
#include "UniversalClass.h"
#include "FetchOctet.h"
#include "LengthExtractor.h"
#include "LengthEmitter.h"
#ifndef MAX_STRUCTURE_FIELDS
#define MAX_STRUCTURE_FIELDS    15
#endif
namespace MMS
{
    /************************************//**
     * \brief Protocol structures serialization routines
     * \details The aim of serialization routines is to implement
     * transparent and easy serialization for MMS protocol PDUs and structures. Example below shows
     * how to turn a humble C-style structure into a MMS protocol structure which can be automatically emitted
     * and extracted by the framework
     * \code
       namespace MMS{
       namespace PDU{
           struct InitiateRequest
           {
           public:
           enum { tag = 0xab };
           typedef Details::InitiateRequestDetail InitRequestDetail;

           InitiateRequest();

           int localDetailCalling;                                  
           short proposedMaxServicesOutstandingCalling;             
           short proposedMaxServicesOutstandingCalled;              
           char proposedDataStructureNestingLevel;                  
           InitRequestDetail initiateRequestDetails;                
           };
       }
       namespace serialization{

       using MMS::PDU::InitiateRequest;

       PDU_OPT_FIELD(InitiateRequest, 0, InitiateRequest::localDetailCalling);
       PDU_FIELD(InitiateRequest, 1, InitiateRequest::proposedMaxServicesOutstandingCalling);
       PDU_FIELD(InitiateRequest, 2, InitiateRequest::proposedMaxServicesOutstandingCalled);
       PDU_OPT_FIELD(InitiateRequest, 3, InitiateRequest::proposedDataStructureNestingLevel);
       PDU_FIELD(InitiateRequest, 4, InitiateRequest::initiateRequestDetails);

       }
       }
     * \endcode
     *
     * \note If structure contains an integral member named "choice", this
     * structure will be treated as of "choice type". When extracting and emitting,
     * only one field will be chosen according to "choice" member value or choice
     * value extracted from the network
     ****************************************/
    namespace serialization
    {
        /************************************//**
         * \brief Placeholder indicating if field does not have context-specific tag
         *
         * \details In most cases, all fields are tagged within context. Certain
         * structures, however, don't use such tags as they can be unambiguously 
         * decoded without them. For example, domain-specific record of ObjectName
         * structure has no context-specific tags
         *
         * \tparam T structure type
         * \tparam ID ID of this field within the protocol structure. Used to identify the field
         * in MMS protocol messages
         *
         ****************************************/
         /************************************//**
         * \brief PDU/payload field definition placeholder
         *
         * \tparam T structure type
         * \tparam ID ID of this field within the protocol structure. Used to identify the field
         * in MMS protocol messages
         *
         ****************************************/
        template <typename T, int ID>
        struct pdu_field
        {
            typedef void field;
            typedef std::false_type implicit;
        };

        template <typename T, int ID>
        struct dist_indexed
        {
            typedef std::true_type type;
        };

        template <typename T, int ID, typename U>
        inline typename dist_indexed<T, ID>::type check_dist_indexed(...)
        {
            return dist_indexed<T, ID>::type();
        };

        namespace Details
        {
            template <typename T>
            inline typename std::enable_if<::ASN1::Tags::TagDef<T>::TAG != -1, unsigned char>::type getTagModifier(const T&)
            {
                return 0x80;
            }

            template <typename T>
            inline typename std::enable_if<::ASN1::Tags::TagDef<T>::TAG == -1, unsigned char>::type getTagModifier(const T&)
            {
                return 0xA0;
            }

            template <typename C, typename U>
            inline C&& emitContextSpecificTag(C&& _ctx, int ID, U& _what)
            {
                return std::move(MMS::Emitters::emitOctet(std::forward<C>(_ctx), (getTagModifier(_what) | ID)));
            }
            /************************************//**
             * \brief Check context specific tag depending on 
             ****************************************/
            ///@{
            template <typename C,  typename U>
            inline bool checkContextSpecificTag(C& _ctx, int ID, U& _what, std::true_type)
            {
                unsigned char _octet = 0;
                if (MMS::Extractors::fetchOctet(_ctx, _octet))
                {
                    return _octet == (getTagModifier(_what) | ID);
                }
                return false;
            }
            template <typename C,  typename U>
            inline bool checkContextSpecificTag(C& _ctx, int ID, U& _what, std::false_type)
            {
                return true;
            }
            ///@}
        }

        /************************************//**
         * \brief Field structure
         *
         * \details Used to define a mandatory field of protocol structure.
         * With help of PDU_FIELD(type, id, member) macro and little template voodoo magic,
         * turns ordinary structures into something the framework knows how
         * to emit and extract.
         *
         * \tparam T PDU or other payload structure type
         * \tparam U Type of the field
         * \tparam ptr Field member pointer within type T
         *
         ****************************************/
        template <class T, class U, U T::*ptr>
        struct field
        {
        public:
            /************************************//**
             * \brief Emitter
             ****************************************/
            template <int ID, class C>
            inline
            C&& emit(
                C&& _ctx,
                const T& _s
                ) const
            {
                auto oldLength = MMS::getContextSize(_ctx);
                _ctx = ::MMS::Emitters::emit(std::forward<C>(_ctx), _s.*ptr);
                if (check_dist_indexed<T, ID, U>(0))          // In most cases, we are distinctly indexed
                {
                    if (!std::remove_reference<C>::type::context_traits::tImplicit())      // Explicit context: we must emit the length before the distinct tag
                    {
                        _ctx = ::MMS::Emitters::emitLength(std::forward<C>(_ctx), oldLength - MMS::getContextSize(_ctx));
                    }
                    _ctx = Details::emitContextSpecificTag(std::forward<C>(_ctx), ID, _s.*ptr);
                }
                return std::move(_ctx);
                
            }
            /************************************//**
             * \brief Extractor
             ****************************************/
            template <int ID, class C>
            inline
            bool fetch(
                C& _ctx,
                T& _s
                ) const
            {
                if (Details::checkContextSpecificTag(_ctx, ID, _s.*ptr, check_dist_indexed<T, ID, U>(0)))
                {
                    if (check_dist_indexed<T, ID, U>(0) && !std::remove_reference<C>::type::context_traits::tImplicit())  // Distinctly indexed and explicit
                    {
                        unsigned int _len = 0;
                        if (MMS::Extractors::fetchLength(_ctx, _len))
                        {
                            return MMS::Extractors::fetch(MMS::Extractors::getSubContext(_ctx, _len), _s.*ptr);
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return MMS::Extractors::fetch(_ctx, _s.*ptr);
                    }
                }
                else
                {
                    return false;
                }
            }
        };
         /************************************//**
         * \brief Optional field structure
         *
         * \details Used to define a mandatory field of protocol structure.
         * With help of PDU_OPT_FIELD macro and little template voodoo magic,
         * turns ordinary structures into something the framework knows how
         * to emit and extract.
         *
         * \tparam T PDU or other payload structure type
         * \tparam U Type of the field
         * \tparam ptr Field member pointer within type T
         * \tparam _dflt default value of the field. When field has this value, it will not be emitted and field
         * will be omitted
         *
         ****************************************/
        template <class T, class U, U T::*ptr>
        struct opt_field
        {
        public:
            /************************************//**
             * \brief Emitter
             *
             * \details Field may be emitted in either implicit or explicit context
             *
             ****************************************/
            template <int ID, class C>
            inline
                C&&  emit(
                C&& _ctx,
                const T& _s
                ) const
            {
                if (!(_s.*ptr == U()))
                {
                    auto oldLength = MMS::getContextSize(_ctx);
                    _ctx = ::MMS::Emitters::emit(std::forward<C>(_ctx), _s.*ptr);
                    if (check_dist_indexed<T, ID, U>(0))          // In most cases, we are distinctly indexed
                    {
                        if (!pdu_field<T, ID>::implicit())     // Explicit field: we must emit the length
                        {
                            _ctx = ::MMS::Emitters::emitLength(std::forward<C>(_ctx), oldLength - MMS::getContextSize(_ctx));
                        }
                        _ctx = Details::emitContextSpecificTag(std::forward<C>(_ctx), ID, _s.*ptr);
                    }
                    return std::move(_ctx);
                }
                else
                {
                    return std::move(_ctx);
                }
            }
            /************************************//**
             * \brief Extractor
             ****************************************/
            template <int ID, class C>
            inline
            bool fetch(
                C& _ctx,
                T& _s
                ) const
            {
                auto old = _ctx;

                if (Details::checkContextSpecificTag(_ctx, ID, _s.*ptr, check_dist_indexed<T, ID, U>(0)))
                {
                    if (check_dist_indexed<T, ID, U>(0) && !std::remove_reference<C>::type::context_traits::tImplicit())  // Distinctly indexed and explicit
                    {
                        unsigned int _len = 0;
                        if (MMS::Extractors::fetchLength(_ctx, _len))
                        {
                            return MMS::Extractors::fetch(MMS::Extractors::getSubContext(_ctx, _len), _s.*ptr);
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (MMS::Extractors::fetch(_ctx, _s.*ptr))
                        {
                            return true;
                        }
                    }
                }

                _s.*ptr = U();
                _ctx = old;
                return true;
            }
        };
        /************************************//**
         * \brief Choice field placeholder
         *
         * \details
         *
         ****************************************/
        template <typename T>
        struct mms_element_choice
        {
            typedef void choice_type;
        };

        template <int ID>
        struct checkID
        {
            enum {value = ID};
          
            static_assert(ID < MAX_STRUCTURE_FIELDS, "Max number of fields exceeded. Consider increasing the value of MAX_STRUCTURE_FIELDS");
        };

        /************************************//**
         * \brief PDU/payload field definition macro
         ****************************************/
#define PDU_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define PDU_IMPLICIT_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define PDU_EXPLICIT_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef field<type, decltype(member), &member> field; typedef std::false_type implicit;};
#define T_PDU_IMPLICIT_FIELD(type, id, member) \
        struct pdu_field<type, checkID<id>::value> { typedef field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define T_PDU_EXPLICIT_FIELD(type, id, member) \
        struct pdu_field<type, checkID<id>::value> { typedef field<type, decltype(member), &member> field; typedef std::false_type implicit;};
        /************************************//**
         * \brief PDU/payload optional field definition macro
         ****************************************/
#define PDU_OPT_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef opt_field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define PDU_OPT_IMPLICIT_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef opt_field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define PDU_OPT_EXPLICIT_FIELD(type, id, member) \
        template <> struct pdu_field<type, checkID<id>::value> { typedef opt_field<type, decltype(member), &member> field; typedef std::false_type implicit;};
#define T_OPT_IMPLICIT_FIELD(type, id, member) \
        struct pdu_field<type, checkID<id>::value> { typedef opt_field<type, decltype(member), &member> field; typedef std::true_type implicit;};
#define T_OPT_EXPLICIT_FIELD(type, id, member) \
        struct pdu_field<type, checkID<id>::value> { typedef opt_field<type, decltype(member), &member> field; typedef std::false_type implicit;};

#define NOINDEX_FIELD(what, id)\
        template <> struct dist_indexed<what, id> { typedef std::false_type type; };

#define T_NOINDEX_FIELD(what, id) struct dist_indexed<what, id> { typedef std::false_type type; };

        namespace Details
        {
            /************************************//**
             * \brief Resolves context to its implicit traits
             ****************************************/
            template <typename C, typename F>
            inline typename std::enable_if<F::implicit::value, typename std::remove_reference<typename C>::type::tImplicit>::type resolveImplicit(C&& _ctx, const F&)
            {
                return std::remove_reference<typename C>::type::tImplicit(_ctx);
            }
            /************************************//**
             * \brief Resolves context to its explicit traits
             ****************************************/
            template <typename C, typename F>
            inline typename std::enable_if<!F::implicit::value, typename std::remove_reference<typename C>::type::tExplicit>::type resolveImplicit(C&& _ctx, const F&)
            {
                return std::remove_reference<typename C>::type::tExplicit(_ctx);
            }
            /************************************//**
             * \brief Emit function selected when provided context type match required for the field
             ****************************************/
            template <int ID, typename C, typename T>
            inline C&& emit_field_helper(C&& _c, const T& _what, std::false_type, std::true_type)
            {
                return std::move(pdu_field<T, ID>::field().emit<ID>(std::forward<C>(_c), _what));
            }
            /************************************//**
             * \brief Emit function selected when provided context type does not match required for the field
             ****************************************/
            template <int ID, typename C, typename T>
            inline C&& emit_field_helper(C&& _c, const T& _what, std::false_type, std::false_type)
            {
                auto newContext = resolveImplicit(std::forward<C>(_c), pdu_field<T, ID>());
                newContext = pdu_field<T, ID>::field().emit<ID>(std::forward<decltype(newContext)>(newContext), _what);
                return std::move(std::remove_reference<typename C>::type(newContext));
            }
            /************************************//**
             * \brief SFINAE fallback or catch-all
             ****************************************/
            template <int ID, typename C, typename T>
            inline C&& emit_field_helper(C&& _c, const T& _what, std::true_type, ...)
            {
                return std::move(_c);
            }
            /************************************//**
             * \brief Fetch function selected when provided context type match required for the field
             ****************************************/
            template <int ID, typename C, typename T>
            inline bool fetch_field_helper(C& _c, T& _what, std::false_type, std::true_type)
            {
                return pdu_field<T, ID>::field().fetch<ID>(std::forward<C>(_c), std::forward<T>(_what));
            }
            /************************************//**
             * \brief Fetch function selected when provided context type does not match required for the field
             ****************************************/
            template <int ID, typename C, typename T>
            inline bool fetch_field_helper(C& _c, T& _what, std::false_type, std::false_type)
            {
                auto context = resolveImplicit(std::forward<C>(_c), pdu_field<T, ID>());
                auto res = pdu_field<T, ID>::field().fetch<ID>(context, std::forward<T>(_what));
                _c = std::remove_reference<C>::type(context);
                return res;
            }
            /************************************//**
             * \brief SFINAE fallback or catch-all
             ****************************************/
            template <int ID, typename C, typename T>
            inline bool fetch_field_helper(C& _c, T& _what, std::true_type, ...)
            {
                return true;
            }
        }

        /************************************//**
         * \brief Field emitter
         ****************************************/
        template <int ID, typename C, typename T>
        inline C&& emit_field(C&& _c, const T& _what)
        {
            return std::move(Details::emit_field_helper<ID>(
                std::forward<C>(_c), 
                _what, 
                std::is_void<pdu_field<T, ID>::field>(),
                std::is_same<std::remove_reference<C>::type::context_traits::tImplicit, pdu_field<T, ID>::implicit>()));
        }
        /************************************//**
         * \brief This namespace holds things that don't work in MSVC
         *
         * \details These things fails do compile presumably because of the bugs
         * in MS Visual Studio 2012 compiler or its partial support of C++11 features
         *
         ****************************************/
        namespace broken_msvc
        {
            /************************************//**
             * \brief Holds the number of fields in the structure
             *
             * \details Used to calculate this number 
             *  at compile time.
             *
             * \todo Try it with gcc, where constexpr work
             *
             ****************************************/
            template <class T>
            struct NumOfFields
            {
                template <int ID>
                static int findMax()
                {
                    if (!std::is_void<pdu_field<T, ID>::field>())
                    {
                        return ID;
                    }
                    else
                    {
                        return findMax<ID-1>();
                    }
                }

                template <>
                static int findMax<0>()
                {
                    return 0;
                }

                static const int MAX = findMax<MAX_STRUCTURE_FIELDS>();
            };
        }


         /************************************//**
         * \brief Recursive Fields emitter 
         *
         * \details A good example of recursive template
         * instantiation inside.
         *
         ****************************************/
        template <int M>
        struct emit_recursively
        {
            template <int ID>
            struct recursive_field_emitter
            {
                template <typename C, typename T>
                inline C&& emit(C&& _c, const T& _what)
                {
                    if (!std::is_void<pdu_field<T, ID>::field>())
                    {
                        _c = emit_field<ID>(std::forward<C>(_c), _what);
                    }
                    return std::move(recursive_field_emitter<ID-1>().emit(std::forward<C>(_c), _what));
                }
            };

            template <>
            struct recursive_field_emitter<0>
            {
                template <typename C, typename T>
                inline C&& emit(C&& _c, const T& _what)
                {
                    return std::move(emit_field<0>(std::forward<C>(_c), _what));
                }
            };


            template <int ID>
            struct chosen_field_emitter
            {
                template <typename C, typename T>
                inline C&& emit(C&& _c, const T& _what, unsigned char _choice)
                {
                    if (!std::is_void<pdu_field<T, ID>::field>() && _choice == ID)
                    {
                        return std::move(emit_field<ID>(std::forward<C>(_c), _what));
                    }
                    else 
                    {
                        return std::move(chosen_field_emitter<ID-1>().emit(std::forward<C>(_c), _what, _choice));
                    }
                }
            };

            template <>
            struct chosen_field_emitter<0>
            {
                template <typename C, typename T>
                inline C&& emit(C&& _c, const T& _what, unsigned char _choice)
                {
                    if (_choice == 0)
                    {
                        return std::move(emit_field<0>(std::forward<C>(_c), _what));
                    }
                    else
                    {
                        return std::move(_c);
                    }
                }
            };


            template <typename C, typename T>
            inline C&& emit(C&& _c, const T& _what)
            {
                return recursive_field_emitter<M>().emit(std::forward<C>(_c), _what);
            }

            template <typename C, typename T>
            inline C&& emit_chosen(C&& _c, const T& _what, unsigned char _choice)
            {
                return chosen_field_emitter<M>().emit(std::forward<C>(_c), _what, _choice);
            }
        };
        /************************************//**
         * \brief Protocol structure emitter
         ****************************************/
        template <typename C, typename T>
        inline C&& emit_fields(C&& _c, const T& _what)
        {
            return std::move(emit_recursively<MAX_STRUCTURE_FIELDS>().emit(std::forward<C>(_c), _what));
        }
        /************************************//**
         * \brief Emits single chosen field for CHOICE elements
         ****************************************/
        template <typename C, typename T>
        inline C&& emit_chosen_field(C&& _c, const T& _what, unsigned char _choice)
        {
            return std::move(emit_recursively<MAX_STRUCTURE_FIELDS>().emit_chosen(std::forward<C>(_c), _what, _choice));
        }
        /************************************//**
         * \brief Field extractor
         ****************************************/
        template <int ID, typename C, typename T>
        inline bool extract_field(C& _c, T& _what)
        {
            return Details::fetch_field_helper<ID>(_c, _what, std::is_void<pdu_field<T, ID>::field>(),
                std::is_same<std::remove_reference<C>::type::context_traits::tImplicit, pdu_field<T, ID>::implicit>());
        }
        /************************************//**
         * \brief Recursive Fields extractor 
         *
         * \details A good example of recursive template
         * instantiation inside.
         *
         ****************************************/
        template <int M>
        struct extract_recursively
        {
            template <int ID>
            struct recursive_fields_extractor
            {
                template <typename C, typename T>
                inline bool extract(C& _c, T& _what)
                {
                    bool result = true; 
                    if (!std::is_void<pdu_field<T, ID>::field>())
                    {
                        result = extract_field<ID>(_c, _what);
                    }
                    return result && recursive_fields_extractor<ID+1>().extract(_c,_what);
                }
            };

            template <>
            struct recursive_fields_extractor<M>
            {
                template <typename C, typename T>
                inline bool extract(C& _c, T& _what)
                {
                    return extract_field<M>(_c, _what);
                }
            };

            template <int ID>
            struct chosen_field_extractor
            {
                template <typename C, typename T>
                inline bool extract(C& _c, T& _what, unsigned char _choice)
                {
                    bool result = false;
                    if (!std::is_void<pdu_field<T, ID>::field>() && _choice == ID)
                    {
                        result = extract_field<ID>(_c, _what);
                    }
                    else 
                    {
                        result = result || chosen_field_extractor<ID+1>().extract(_c,_what, _choice);
                    }
                    return result;
                }
            };

            template <>
            struct chosen_field_extractor<M>
            {
                template <typename C, typename T>
                inline bool extract(C& _c, T& _what, unsigned char _choice)
                {
                    if (_choice == M)
                    {
                        return extract_field<M>(_c, _what);
                    }
                    else
                    {
                        return false;
                    }
                }
            };

            template <typename C, typename T>
            inline bool fetch_fields(C& _c, T& _what)
            {
                return recursive_fields_extractor<0>().extract(_c, _what);
            }

            template <typename C, typename T>
            inline bool fetch_chosen(C& _c, T& _what, unsigned char _choice)
            {
                return chosen_field_extractor<0>().extract(_c, _what, _choice);
            }
        };


        /************************************//**
         * \brief Fetches fields of structure recursively
         *
         * \note Supports structures of up to 15 fields.
         *
         ****************************************/
        template <typename C, typename T>
        inline bool fetch_fields(C& _c, T& _what)
        {
            return extract_recursively<MAX_STRUCTURE_FIELDS>().fetch_fields(_c, _what);
        }

        /************************************//**
         * \brief Extract specific field
         *
         * \note Extracts field of given ID.
         * \returns True if field exists and is successfully extracted.
         * False otherwise
         *
         ****************************************/
        template <typename C, typename T>
        inline bool fetch_chosen_field(C& _c, T& _what, unsigned char _choice)
        {
            return extract_recursively<MAX_STRUCTURE_FIELDS>().fetch_chosen(_c, _what, _choice);
        }
    }

    namespace PDU
    {
        namespace Details
        {
             /************************************//**
             * \brief Protocol PDU element emitter
             *
             * \details Emits the protocol PDU according to
             * MMS/ASN.1 rules. Uses template voodoo magic from serialization.h
             * Relies on fields to be defined using PDU_FIELD and PDU_OPT_FIELD macro.
             * 
             ****************************************/
            ///@{
            template <typename C, typename T>
            inline C&& emitPduElement(C&& _c, const T& _what, decltype(T::choice)*)
            {
                static_assert(std::remove_reference<C>::type::context_traits::tImplicit::value != true, "CHOICE elements must be emitted using explicit context only");
                // This will emit the value of the chosen field and length, and even a tag!
                return std::move(::MMS::serialization::emit_chosen_field(std::forward<C>(_c), _what, _what.choice)); 

            }

            template <typename C, typename T>
            inline C&& emitPduElement(C&& _c, const T& _what, ...)
            {
                auto oldSize = ::MMS::getContextSize(_c);
                _c = ::MMS::serialization::emit_fields(std::forward<C>(_c), _what);
                return std::move(::MMS::Emitters::emitTag(::MMS::Emitters::emitLength(std::forward<C>(_c), oldSize - ::MMS::getContextSize(_c)), _what));
            }
            ///@}

             /************************************//**
             * \brief Protocol PDU element extractor
             *
             * \details Extracts the protocol PDU according to
             * MMS/ASN.1 rules. Uses template voodoo magic from serialization.h
             * Relies on fields to be defined using PDU_FIELD and PDU_OPT_FIELD macro.
             *
             * \note if PDU extraction fails, context is not modified
             * \note Has two cases - if type T defines an enum member "choice", it 
             * indicates that the type is MMS/ASN.1 choice and only one field needs to be
             * extracted. If no such member exists, fields are fetched as normal
             * \note SFINAE used. Here be dragons!
             * 
             ****************************************/
            ///@{
            template <typename C, typename T>
            inline bool extractPDUElement(C& _c, T& _what, decltype(T::choice)*)
            {
                static_assert(C::context_traits::tImplicit::value != true, "CHOICE elements must be extracted using explicit context only");
                auto old = _c;

                unsigned char octet = 0;
                auto _copy = _c;
                if (::MMS::Extractors::fetchOctet(_copy, octet))
                {
                    _what.choice = (decltype(T::choice)) (octet & 0x1F);        // TODO: this may need to be changed for values larger than 31
                    if (::MMS::serialization::fetch_chosen_field(_c, _what, _what.choice))
                    {
                        return true;
                    }
                }

                _c = old;
                return false;
            }

            template <typename C, typename T>
            inline bool extractPDUElement(C& _c, T& _what, ...)
            {
                auto old = _c;
                if (checkTag(_c, _what))
                {
                    unsigned int _len = 0;
                    if (::MMS::Extractors::fetchLength(_c, _len))
                    {
                        if (::MMS::serialization::fetch_fields(::MMS::Extractors::getSubContext(_c, _len), _what))
                        {
                            return true;
                        }
                    }
                }
                _c = old;
                return false;
            }
            ///@}
        }
    }

    namespace Emitters
    {
        /************************************//**
         * \brief Common emitter for protocol PDUs and detail structures
         *
         * \details This emitter is only enabled if emitted type
         * defines at least one PDU field
         *
         ****************************************/
        template <typename Context, typename T>
        inline 
        typename std::enable_if<!std::is_void<typename MMS::serialization::pdu_field<T, 0>::field>::value, typename std::remove_reference<Context>::type>::type&& 
        emit(Context&& _ctx, const T& _Value)
        {
            return std::move(::MMS::PDU::Details::emitPduElement(std::forward<Context>(_ctx), _Value, 0));
        };
    }

    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Common extractor for PDUs and PDU elements
             *
             * \details This extractor is only enabled if type being extracted
             * defines at least one PDU field
             *
             ****************************************/
            template <typename Context, typename T>
            inline 
            typename std::enable_if<!std::is_void<typename MMS::serialization::pdu_field<T, 0>::field>::value, bool>::type 
            extract(Context& _ctx, T& _Value)
            {
                return ::MMS::PDU::Details::extractPDUElement(_ctx, _Value, 0);
            };
        }
    }
}


