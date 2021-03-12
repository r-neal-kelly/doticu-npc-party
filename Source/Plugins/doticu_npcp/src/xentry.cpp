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

}}
