#ifndef __UNIQUERESOURCE__

#define __UNIQUERESOURCE__

namespace ss
{
    template<typename TypeResource, TypeResource DefaultResource>
    class UniqueResource
    {
        public:
            UniqueResource(): _resource{DefaultResource}
            {}

            void set_resource(TypeResource _new_resource = DefaultResource)
            {
                _resource = _new_resource;
            }

            TypeResource get_resource() const { return _resource; }

            ~UniqueResource(){ this->reset_resource(); }

            void reset_resource()
            {
                if (_resource != DefaultResource)
                    _resource = DefaultResource;
            }

            //overloading bool() operator
            operator bool() const
            {
                return _resource != DefaultResource;
            }

        private:
            TypeResource _resource;
    };
}

#endif