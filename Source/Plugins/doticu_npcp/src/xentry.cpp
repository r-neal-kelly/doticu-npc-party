/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp { namespace Papyrus {

    void XEntry_t::Add_Clean_XList(XList_t* xlist, Reference_t* owner)
    {
        size_t xdata_count = XList::Clean_For_Move(xlist, owner);
        if (xdata_count == 0) {
            Increment(1);
            XList::Destroy(xlist);
        } else if (xdata_count == 1 && xlist->m_data->GetType() == kExtraData_Count) {
            Increment(XList::Count(xlist));
            XList::Destroy(xlist);
        } else {
            Add_XList(xlist);
        }
    }

    void XEntry_t::Clean_XLists(Int_t from_bentry_count, Reference_t* to_reference)
    {
        if (xlists && to_reference) {
            std::vector<XList_t*> buffer;
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist) {
                    XList::Validate(xlist, delta_count, from_bentry_count);
                    buffer.push_back(xlist);
                }
            }
            for (size_t idx = 0, count = buffer.size(); idx < count; idx += 1) {
                XList_t* xlist = buffer[idx];
                size_t xdata_count = XList::Clean_For_Move(xlist, to_reference);
                if (xdata_count == 0) {
                    Remove_XList(xlist);
                    Increment(1);
                    XList::Destroy(xlist);
                } else if (xdata_count == 1 && xlist->m_data->GetType() == kExtraData_Count) {
                    Remove_XList(xlist);
                    Increment(XList::Count(xlist));
                    XList::Destroy(xlist);
                }
            }
        }
    }

}}
